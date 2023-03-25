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
   std::string strtemp4 = "D";
   std::string strtemp5 = "E";
   std::string strtemp6 = "F";
   std::string strtemp7 = "G";
   std::string strtemp8 = "H";
   std::string strtemp9 = "I";
   std::string strtemp10 = "J";
   std::string strtemp11 = "K";
   std::string strtemp12 = "L";


   Container temp(1, 1, 10, strtemp);
   Container temp2(1, 1, 20, strtemp2);
   Container temp3(1, 1, 30, strtemp3);
   Container temp4(1, 1, 40, strtemp4);
   Container temp5(1, 1, 50, strtemp5);
   Container temp6(1, 1, 60, strtemp6);
   Container temp7(1, 1, 70, strtemp7);
   Container temp8(1, 1, 80, strtemp8);
   Container temp9(1, 1, 90, strtemp9);
   Container temp10(1, 1, 100, strtemp10);
   Container temp11(1, 1, 110, strtemp11);
   Container temp12(1, 1, 120, strtemp12);

   ship.bay[0][0] = temp;
   ship.bay[0][1] = temp2;
   ship.bay[0][2] = temp3;
   ship.bay[0][3] = temp4;
   ship.bay[0][4] = temp5;
   ship.bay[0][5] = temp6;
   ship.bay[0][6] = temp7;
   ship.bay[0][7] = temp8;
   ship.bay[0][8] = temp9;
   ship.bay[0][9] = temp10;
   ship.bay[0][10] = temp11;
   ship.bay[0][11] = temp12;


   generateManifest(ship, nameOfTest);
}

