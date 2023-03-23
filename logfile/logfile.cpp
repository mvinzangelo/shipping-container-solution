#include "logfile.h"
#include "../manifest/manifest.h"
#include <string>

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