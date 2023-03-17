#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

/*
Format of each manifest line:
[RowInt, ColumnInt], {WeightInt}, Name/NAN/Unused
Example: [01, 01], {00000}, NAN

This parse is mainly proof of concept; we can easily parse through a manifest and extract information.
This test simply gets the information from each row, and outputs it.
*/

/*
Struct defining a container with it's characteristics, with default and parameterized constructor.
PLEASE NOTE: This struct SHOULD be moved to another file! It is only here for testing purposes.
*/

// TODO: Move Container and Ship structs to a different file.

struct Container {
   short row;
   short column;
   int weight;
   std::string name;
   Container() : row(-1), column(-1), weight(0), name("NAN") {}
   Container(int row, int column, int weight, std::string& name) : 
   row(row), column(column), weight(weight), name(name) {}
};

/*
   Design choices:
   "Why are arrays type Container and not Container*?""
   Contiguous allocation of literal Container objects will lead to faster speed since they do not have a lot of data (biggest reason)
   Dynamic allocation is not necessary since we are working with fixed sizes (only one class of ship serviced)
   Only modifications made to ship are swapping of containers, which would be more complicated with pointers.
      - Note: might be better to protect the fields of the Container struct to avoid accidental modification, since we do NOT modify the containers.
*/

struct Ship {
   Container ship[8][12];
   Container buffer[4][24];
   std::string manifestName;
   int numContainers;
   Ship() : numContainers(0) {}
   Ship(std::string& name);
   int getPortWeight();
   int getStarbordWeight();
};

Ship::Ship(std::string& name)
{
   numContainers = 0;
   std::ifstream file(name);
   if (file.is_open())
   {
      char c;
      int row, column, weight;
      std::string name, line;
      Container currentContainer;
      char c;
      int row, column, weight;
      std::string name, line;
      Container currentContainer;
      while (std::getline(file, line))
         {
            std::cout << line << '\n'; // Debug
            std::stringstream s(line);
            s >> std::skipws >> c >> row >> c >> column >> c >> c >> c >> weight >> c >> c >> name;
            // if (name == "NAN") std::cout << "ALERT: This slot does not exist! ";
            // else if (name == "UNUSED") std::cout << "ALERT: This slot is empty! ";
            std::cout << "Row: " << row << "\n" << "Column: " << column << '\n' << "Weight: " << weight << '\n' << "Name: " << name << '\n';
            currentContainer = Container(row, column, weight, name);

            ship[row - 1][column - 1] = currentContainer;
            if (name != "NAN" && name != "UNUSED") numContainers++;

         }
         file.close();
   }
   else
   {
      std::cout << "ERROR: Unable to open " << name << ".\n";
   }
}

Ship currentShip;

void populateShip() // test function
{
   // Get the manifest name, and open it.
   std::string manifest;
   std::cout << "Enter name of manifest: ";
   std::getline(std::cin, manifest);
   std::cout << "\nParsing " << manifest << "...\n";
   std::ifstream file(manifest);

   // Parse through the manifest, getting all necessary information.
   if (file.is_open())
   {
      char c;
      int row, column, weight;
      std::string name, line;
      Container currentContainer;
      

      while (std::getline(file, line))
      {
         std::cout << line << '\n'; // Debug
         std::stringstream s(line);
         s >> std::skipws >> c >> row >> c >> column >> c >> c >> c >> weight >> c >> c >> name;
         // if (name == "NAN") std::cout << "ALERT: This slot does not exist! ";
         // else if (name == "UNUSED") std::cout << "ALERT: This slot is empty! ";
         std::cout << "Row: " << row << "\n" << "Column: " << column << '\n' << "Weight: " << weight << '\n' << "Name: " << name << '\n';
         currentContainer = Container(row, column, weight, name);

         currentShip.ship[row - 1][column - 1] = currentContainer;
         if (name != "NAN" && name != "UNUSED") currentShip.numContainers++;

      }
      file.close();
   }
   else
   {
      std::cout << "ERROR: Unable to open file.\n";
      return;
   }
   // Must iterate backwards to print first row on bottom
   for (int i = 7; i >= 0; i--)
   {
      for (int j = 0; j < 12; j++)
      {
         std::cout << currentShip.ship[i][j].name[0] << ' ';
      }
      std::cout << '\n';
   }

   std::cout << "Successfully parsed through " << manifest << ", which has " << currentShip.numContainers << " containers" << ".\n";
}