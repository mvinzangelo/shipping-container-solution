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
// Compile with g++ main.cpp ../logfile/logfile.cpp ../manifest/manifest.cpp

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
   
   for (int i = 0; i < 8; i++)
   {
      for (int j = 0; j < 12; j++)
      {
         ship.bay[i][j].row = i + 1;
         ship.bay[i][j].column = j + 1;
         ship.bay[i][j].name = "UNUSED";
      }
   }

   // DECLARE CONTAINERS IN HERE
   std::string strtemp = "A";
   std::string strtemp2 = "B";
   std::string strtemp3 = "C";

   Container temp(1, 1, 50, strtemp);
   Container temp2(1, 1, 45, strtemp2);
   Container temp3(1, 1, 5, strtemp3);

   ship.bay[0][4] = temp3;
   ship.bay[0][5] = temp;
   ship.bay[0][6] = temp2;

   generateManifest(ship, nameOfTest);
}

