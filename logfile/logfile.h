#ifndef LOGFILE_H
#define LOGFILE_H
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "../manifest/manifest.h"

// Macros to make it easy to define onload/offload to log
#define ONLOAD 0
#define OFFLOAD 1

class LogFile
{
    private:
        std::ofstream logFile;
        std::string currentLogFileName;
        bool validFileName;
        std::string getTimestampString();
    public:
        LogFile();
        ~LogFile();
        void logEmployeeCheckIn(std::string&);
        void logAtomicMove(std::string&, int);
        void logManifestOpen(Ship&);
        void logManifestFinish(Ship&);
        void getOperatorMessage();
};

LogFile::LogFile()
{
    validFileName = false;
    std::ifstream configFile("config.txt");
    if (configFile.peek() == std::ifstream::traits_type::eof())
    {
        std::cout << "ALERT: Configuration file is empty. If this is your first time starting the program, ignore this alert." 
                  << " If not, please contact Shipping Container Solutions tech support immediately.\n";
        configFile.close();
    }
    else
    {
        std::getline(configFile, currentLogFileName);
        validFileName = true;
        configFile.close();
    }
    if (validFileName) 
    {
        char option;
        std::cout << "Would you like to start a new logfile? (y/n): ";
        while (option != 'n' && option != 'y')
        {
            std::cin >> option;
            if (option == 'y' || option == 'n') break;
            else std::cout << "\nInvalid input, please try again (y/n): ";
        }

        if (option == 'n')
        {
            std::cout << "Resuming logging in " << currentLogFileName << ".\n";
            logFile.open(currentLogFileName, std::ios::app);
            return;
        }
    }
    int logicalYear;
    std::cout << "\nCreating new log file. Please enter logical year to append to end of logfile: ";
    std::cin >> logicalYear;
    std::string logFileName = "KeoghLongBeach" + std::to_string(logicalYear) + ".txt";
    currentLogFileName = logFileName;
    std::ofstream saveLogFileName("config.txt");
    saveLogFileName << currentLogFileName;
    logFile.open(logFileName, std::ios::app);
}

LogFile::~LogFile()
{
    logFile.close();
}

// Returns timestamp in format of: Month Day, Year: HH:MM:SS (where HH:MM:SS is in 24 hour time)
// Example: March 16, 2023: 22:49:38
std::string LogFile::getTimestampString()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&now_t);

    char timestamp[100];
    std::strftime(timestamp, 100, "%B %d, %Y: %H:%M:%S", &tm);
    return timestamp;
}

void LogFile::logEmployeeCheckIn(std::string& name)
{
    this->logFile << getTimestampString() << ": " << name << " has checked in.\n";
}

void LogFile::logAtomicMove(std::string& containerName, int loadType)
{
    std::string timestamp = getTimestampString();

    if (loadType == ONLOAD)
    {
        this->logFile << timestamp << ": \"" << containerName << '\"' << " is onloaded.\n"; 
    }
    else if (loadType == OFFLOAD)
    {
        this->logFile << timestamp << ": \"" << containerName << '\"' << " is offloaded.\n"; 
    }
}
void LogFile::logManifestOpen(Ship& ship)
{
    std::string timestamp = getTimestampString();
    this->logFile << timestamp << ": " << "Manifest " << ship.manifestName << " is opened, there are " << ship.getNumContainers() << " on the ship.\n";
}
void LogFile::logManifestFinish(Ship& ship)
{
    std::string timestamp = getTimestampString();
    std::string oldManifestName = ship.manifestName;
    std::string newManifestName;

    auto findFileExtension = oldManifestName.find_last_of('.');
    if (findFileExtension != std::string::npos)
    {
        newManifestName = oldManifestName.substr(0, findFileExtension);
        newManifestName += "OUTBOUND";
        newManifestName += oldManifestName.substr(findFileExtension);
    }
    else
    {
        newManifestName = oldManifestName + "OUTBOUND";
    }
    this->logFile << timestamp << ": " << "Finished a cycle. Manifest " << newManifestName << " was written to desktop, and a reminder pop-up to operator to send file was displayed.\n";
}
void LogFile::getOperatorMessage()
{
    std::string message;
    std::cout << "Input your message to the logfile: ";
    getline(std::cin >> std::ws, message);
    this->logFile << getTimestampString() << ": " << message << '\n';
}

#endif