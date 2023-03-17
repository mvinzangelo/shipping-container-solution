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

struct Container {
   short row;
   short column;
   int weight;
   std::string name;
   Container() : row(-1), column(-1), weight(0), name("NAN") {}
   Container(int row, int column, int weight, std::string& name) : 
   row(row), column(column), weight(weight), name(name) {}
};

struct Ship {
   Container ship[8][12];
   Container buffer[4][24];
   std::string manifestName;
   int numContainers;
   Ship() : numContainers(0) {}
   Ship(std::string& name) : manifestName(name), numContainers(0) {}
};

//Container ship[8][12];
Ship currentShip;

/*
void parseTest()
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

      while (std::getline(file, line))
      {
         // std::cout << line << '\n'; // Debug
         std::stringstream s(line);
         s >> std::skipws >> c >> row >> c >> column >> c >> c >> c >> weight >> c >> c >> name;
         if (name == "NAN") std::cout << "ALERT: This slot does not exist! ";
         else if (name == "UNUSED") std::cout << "ALERT: This slot is empty! ";
         
         std::cout << "Row: " << row << 
                      " Column: " << column << 
                      " Weight: " << weight << 
                      " Name: " << name << '\n';
      }
      file.close();
   }
   else
   {
      std::cout << "ERROR: Unable to open file.\n";
      return;
   }

   std::cout << "Successfully parsed through " << manifest << ".\n";
}
*/

void populateShip()
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