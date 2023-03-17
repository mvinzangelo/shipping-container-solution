#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

// Macros to make it easy to define onload/offload to log
#define ONLOAD 0
#define OFFLOAD 1

class LogFile
{
    private:
        std::ofstream logFile;
        std::string currentLogFileName;
        bool validFileName;
    public:
        LogFile();
        ~LogFile();
        void logEmployeeCheckIn(std::string&);
        void logAtomicMove(std::string&, int);
        void logManifestOpen();
        void logManifestClose();
        void getOperatorMessage();
        void restartLogFile();
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
}

LogFile::~LogFile()
{
    logFile.close();
}

void LogFile::logEmployeeCheckIn(std::string& name)
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&now_t);

    char buffer[80];
    std::strftime(buffer, 80, "%B %d, %Y: %H:%M:%S", &tm);

    this->logFile << buffer << ": " << name << " has checked in.\n";
}

void LogFile::logAtomicMove(std::string&, int)
{

}
void LogFile::logManifestOpen()
{

}
void LogFile::logManifestClose()
{

}
void LogFile::getOperatorMessage()
{

}

void LogFile::restartLogFile()
{
    char option;
    if (validFileName) 
    {
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
    
    //std::rename(const_cast<char*>(oldName.c_str()), const_cast<char*>(newName.c_str()));
    // CHANGE logFile variable to track new filename! 
}