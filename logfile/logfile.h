#include <iostream>
#include <fstream>
#include <string>

void initializeLogFile()
{
    std::cout << "Initializing new log file...\n";
    std::ofstream logFile("KeoghLongBeach.txt");
    if (logFile.is_open())
    {
        std::cout << "Log file successfully initialized.\n";
    }
    else
    {
        std::cout << "ERROR: Could not initialize log file!\n";
        // handle this potential error somehow
    }
}