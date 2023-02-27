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