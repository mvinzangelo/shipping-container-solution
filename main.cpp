//#include "mainwindow.h"

//#include <QApplication>
#include <iostream>
#include "manifest/manifest.h"


int main(int argc, char *argv[])
{
    std::string manifestName = "Ships/ShipCase1.txt";
   // std::cout << "Input a manifest name: ";
   // std::getline(std::cin,manifestName);
   // std::cout << '\n';
    Ship currentShip(manifestName);
    Container* currentContainer;
    currentShip.bay[0][0].name = "Walmart";
    currentShip.bay[1][0].name = "Target";
    for (int i = 7; i >=0; i--)
    {
        for (int j = 0; j < 12; j++)
        {
            std::cout << currentShip.bay[i][j].name[0] << ' ';
        }
        std::cout << '\n';
    }

    for (int i = 7; i >= 0; i--)
   {
      for (int j = 0; j < 12; j++)
      {
         if (currentShip.bay[i][j].name != "NAN" && currentShip.bay[i][j].name != "UNUSED")
         {
            currentContainer = &currentShip.bay[i][j];
            std::cout << "Depth of " << currentContainer->name << ": " << currentContainer->getDepth(currentShip) << '\n';
         }
      }
   }

   std::cout << currentShip.bay[1][0].getDepth(currentShip) << std::endl;

    return 0;
}