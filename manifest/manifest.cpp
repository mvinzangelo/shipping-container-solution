#include "manifest.h"


Ship::Ship(std::string& name)
{
   std::ifstream file(name);
   manifestName = name;
   if (file.is_open())
   {
      char c;
      int row, column, weight;
      std::string name, line;
      Container currentContainer;
      while (std::getline(file, line))
         {
            // std::cout << line << '\n'; // Debug
            std::stringstream s(line);
            s >> std::skipws >> c >> row >> c >> column >> c >> c >> c >> weight >> c >> c;
            std::getline(s, name);
            name.erase(0, 1);
            // if (name == "NAN") std::cout << "ALERT: This slot does not exist! ";
            // else if (name == "UNUSED") std::cout << "ALERT: This slot is empty! ";
            // std::cout << "Row: " << row << "\n" << "Column: " << column << '\n' << "Weight: " << weight << '\n' << "Name: " << name << '\n';
            currentContainer = Container(row, column, weight, name);

            bay[row - 1][column - 1] = currentContainer;
            // if (name != "NAN" && name != "UNUSED") numContainers++;

         }
         file.close();
   }
   else
   {
      std::cout << "ERROR: Unable to open " << name << ".\n";
   }
}

short Container::getDepth(Ship& ship)
{
   try
   {
      short depth = 0;
      
      if (ship.bay[row - 1][column - 1].name != name || ship.bay[row - 1][column - 1].name == "NAN") 
      {
         throw std::invalid_argument("ERROR: getDepth called on incorrect container.\n");
         
      }
      else
      {
         for (int i = row; i < 8; i++)
         //for (int i = row; i < 8; i++)
         {  
            if(ship.bay[i][column - 1].name != "UNUSED"){ depth++; }
            else{ break; }      
         }
         return depth;
      }
      
   }
   catch (const std::exception& e)
   {
      std::cout << "Caught an exception: " << e.what() << "\n"; 
   }
   return -1;
}

int Ship::getPortWeight()
{
   int weight = 0;
   for (int i = 0; i < 8; i++)
   {
      for (int j = 0; j < 6; j++)
      {
         weight += bay[i][j].weight;
      }
   }
   return weight;
}

int Ship::getStarbordWeight()
{
   int weight = 0;
   for (int i = 0; i < 8; i++)
   {
      for (int j = 6; j < 12; j++)
      {
         weight += bay[i][j].weight;
      }
   }
   return weight;
}

int Ship::getNumContainers()
{
   int numContainers = 0;
   for (int i = 0; i < 8; i++)
   {
      for (int j = 0; j < 12; j++)
      {
         if (bay[i][j].name != "UNUSED" && bay[i][j].name != "NAN")
         {
            numContainers++;
         }
      }
   }
   return numContainers;
}

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