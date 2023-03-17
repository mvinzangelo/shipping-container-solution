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
        std::ofstream logFile/*= "KeoghLongBeach.txt"*/;
    public:
        LogFile() : logFile("KeoghLongBeach.txt", std::ios::app) {};
        ~LogFile();
        void logEmployeeCheckIn(std::string&);
        void logAtomicMove(std::string&, int);
        void logManifestOpen();
        void logManifestClose();
        void getOperatorMessage();
        void restartLogFile();
};

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
    std::cout << "Would you like to start a new logfile? (y/n): ";
    while (option != 'n' && option != 'y')
    {
        std::cin >> option;
        if (option == 'y' || option == 'n') break;
        else std::cout << "\nInvalid input, please try again (y/n): ";
    }

    if (option == 'n') return;
    
    int logicalYear;
    std::string oldName = "KeoghLongBeach.txt";
    std::cout << "Saving log file, please enter logical year of current logfile: ";
    std::cin >> logicalYear;
    std::string newName = "KeoghLongBeach" + std::to_string(logicalYear) + ".txt";
    //std::rename(const_cast<char*>(oldName.c_str()), const_cast<char*>(newName.c_str()));
    // CHANGE logFile variable to track new filename! 
}