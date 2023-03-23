#include "manifest.h"

int main(int argc, char *argv[])
{
   std::string manifestName;
   std::cout << "Input a manifest name: ";
   std::getline(std::cin, manifestName);
   std::cout << '\n';
   Ship currentShip(manifestName);
   Container* currentContainer;
   for (int i = 7; i >= 0; i--)
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
   std::cout << "Port weight: " << currentShip.getPortWeight() << '\n';
   std::cout << "Starboard weight: " << currentShip.getStarbordWeight() << '\n';
   std::cout << "Number of Containers on ship: " << currentShip.getNumContainers() << '\n';
   
   return 0;
}