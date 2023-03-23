#include "logfile.h"
#include "../manifest/manifest.h"
#include <string>

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
    saveLogFileName.close();
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

    std::string homeDir;
    std::string newManifestPath;

    #ifdef _WIN32 // If running on Windows
        const char* userProfile = std::getenv("USERPROFILE");
        if (userProfile != nullptr) {
            homeDir = userProfile;
            newManifestPath = homeDir + "\\Desktop\\" + newManifestName;
        }
    #else // If running on Linux or other Unix-based OS
        const char* home = std::getenv("HOME");
        if (home != nullptr) {
            homeDir = home;
            newManifestPath = homeDir + "/" + newManifestName;
        }
    #endif
    std::ofstream newManifest(newManifestPath);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            newManifest << "[" << std::setw(2) << std::setfill('0') << ship.bay[i][j].row
                        << "," << std::setw(2) << std::setfill('0') << ship.bay[i][j].column
                        << "], {" << std::setw(5) << std::setfill('0') << ship.bay[i][j].weight
                        << "}, " << ship.bay[i][j].name;
            if (i == 7 && j == 11) break;
            newManifest << '\n';
        }
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


int main(int argc, char *argv[])
{
    LogFile log;
    std::string name = "Joshua Candelaria";
    std::string container = "Container";
    std::string manifestName;
    std::cout << "Input a manifest name: ";
    std::getline(std::cin >> std::ws, manifestName);
    std::cout << '\n';
    Ship currentShip(manifestName);
    
    log.logEmployeeCheckIn(name);
    log.logAtomicMove(container, ONLOAD);
    log.getOperatorMessage();
    log.logAtomicMove(container, OFFLOAD);
    log.logManifestOpen(currentShip);
    log.logManifestFinish(currentShip);
}