#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include "../logfile/logfile.h"
#include "../manifest/manifest.h"

// Used to generate manifests to test

void generateManifest(Ship& ship, std::string& nameOfTest)
{
    std::ofstream newManifest(nameOfTest);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            newManifest << "[" << std::setw(2) << std::setfill('0') << i + 1
                        << "," << std::setw(2) << std::setfill('0') << j + 1
                        << "], {" << std::setw(5) << std::setfill('0') << ship.bay[i][j].weight
                        << "}, " << ship.bay[i][j].name;
            if (i == 7 && j == 11) break;
            else newManifest << '\n';
        }
    }
}

int main()
{
   Ship ship;
   std::string nameOfTest;
   std::cout << "Input name of test (don't write .txt, I got it): ";
   getline(std::cin, nameOfTest);
   nameOfTest += ".txt";
   
   // DECLARE CONTAINERS IN HERE



   generateManifest(ship, nameOfTest);
}

