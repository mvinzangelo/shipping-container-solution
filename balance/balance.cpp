#include "balance.h"
#include "../manifest/manifest.h"

//main to test balancing 
int main(int argc, char *argv[])
{
   std::string manifestName;
   std::cout << "Input a manifest name: ";
   std::getline(std::cin, manifestName);
   std::cout << '\n';
   Ship currentShip(manifestName);
   Container* currentContainer;

   printShip(currentShip); 

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

    //testing operators picking up 
    //vector<Ship>visited; 

    balanceSearch(currentShip,1); 


   return 0;
}