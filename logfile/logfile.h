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
        std::ofstream logFile /*= "KeoghLongBeach.txt"*/;
    public:
        LogFile() : logFile("KeoghLongBeach.txt") {};
        void logEmployeeCheckIn(std::string&);
        void logAtomicMove(std::string&, int);
        void logManifestOpen();
        void logManifestClose();
        void getOperatorMessage();
        void restartLogFile();
};

void LogFile::logEmployeeCheckIn(std::string& name)
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&now_t);

    char buffer[80];
    std::strftime(buffer, 80, "%B %d, %Y: %H:%M:%S", &tm);

    this->logFile << buffer << ": " << name << " has checked in.\n";
}