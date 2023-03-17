#include "logfile.h"
#include <string>

int main(int argc, char *argv[])
{
    LogFile log;
    //log.restartLogFile();
    std::string name = "Joshua Candelaria";
    std::string container = "Container";
    log.logEmployeeCheckIn(name);
    log.logAtomicMove(container, ONLOAD);
    log.getOperatorMessage();
    log.logAtomicMove(container, OFFLOAD);
}