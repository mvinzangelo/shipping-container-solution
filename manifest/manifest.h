#ifndef MANIFEST_H
#define MANIFEST_H
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

struct Ship;

// TODO: Move Container and Ship structs to a different file.
struct Container
{
   short row;
   short column;
   int weight;
   std::string name;
   Container() : row(-1), column(-1), weight(0), name("UNUSED") {}
   Container(int row, int column, int weight, std::string &name) : row(row), column(column), weight(weight), name(name) {}
   short getDepth(Ship &);
   bool isContainer();
};

/*
   Design choices:
   "Why are arrays type Container and not Container*?""
   Contiguous allocation of literal Container objects will lead to faster speed since they do not have a lot of data (biggest reason)
   Dynamic allocation is not necessary since we are working with fixed sizes (only one class of ship serviced)
   Only modifications made to ship are swapping of containers, which would be more complicated with pointers.
      - Note: might be better to protect the fields of the Container struct to avoid accidental modification, since we do NOT modify the containers.
*/

struct Ship
{
   Container bay[8][12];
   Container buffer[4][24];
   std::string manifestName;
   std::string manifestPath;
   // int numContainers;
   Ship() {}
   Ship(std::string &name);
   int getPortWeight();
   int getStarbordWeight();
   int getNumContainers();
};

#endif