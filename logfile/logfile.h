#include <iostream>
#include <fstream>
#include <string>

#define ONLOAD 0
#define OFFLOAD 1

class LogFile 
{
    private:
        std::ofstream logFile /*= "KeoghLongBeach.txt"*/;
    public:
        LogFile() : logFile("KeoghLongBeach.txt");
        void logEmployeeCheckIn(std::string&);
        void logAtomicMove(std::string&, int);
        void logManifestOpen();
        void logManifestClose();
        void getOperatorMessage();
        void restartLogFile();
};