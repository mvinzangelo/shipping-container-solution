#include "logfile.h"
#include <string>

int main(int argc, char *argv[])
{
    LogFile log;
    log.restartLogFile();
    std::string name = "Joshua Candelaria";
    log.logEmployeeCheckIn(name);
}