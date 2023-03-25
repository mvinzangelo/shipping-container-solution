#ifndef LOGFILE_H
#define LOGFILE_H
#include <cstdlib>
#include <iostream>
#include <iomanip>
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
        void initLogFile(int, int);
        void logEmployeeCheckIn(std::string&);
        void logEmployeeCheckOut(std::string&);
        void logAtomicMove(std::string&, int);
        void logManifestOpen(Ship&);
        void logManifestFinish(Ship&);
        void getOperatorMessage(std::string&);
};

#endif