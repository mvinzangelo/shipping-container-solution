#ifndef MANIFEST_H
#define MANIFEST_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <vector> 
#include <algorithm> 


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
   Container(const Container& other) : row(other.row), column(other.column), weight(other.weight), name(other.name) {}
   short getDepth(Ship &);
   bool isContainer();
   Container& operator=(const Container& other);
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
   int crainX;
   int crainY;
   // int numContainers;
   Ship() {}
   Ship(std::string &name);
   Ship(const Ship&);
   int getPortWeight();
   int getStarbordWeight();
   int getNumContainers();
   void printShip();
   void printDepths();

   //array to hold children that can be expanded for balancing
   std::vector<Ship> balanceChild;  

   //variable to hold the container currently being held by the crane
   //when picking up for balancing 
   Container onCrane; 

   //keeps track of what column the crane was on
   //to help avoid repeated staes 
   int craneLocation = -1; 
   //variables that hold values for heuristic,depth,and best cost 
   int h = 0; 
   int depth = 0;
   int fn = 0; 
   
   //comparison operator for ships (used for inserting into priority queue)
   bool operator< (const Ship& rhs)const {

      return(this->fn < rhs.fn);

   }
   Ship& operator=(const Ship&);
};

#endif