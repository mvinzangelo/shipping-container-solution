#include "manifest.h"
#include "../logfile/logfile.h"

Ship::Ship(std::string &path)
{
   manifestPath = path;
   std::ifstream file(path);
#ifdef _WIN32
   auto findFileExtension = manifestPath.find_last_of('\\');
#else
   auto findFileExtension = manifestPath.find_last_of('/');
#endif
   if (findFileExtension != std::string::npos)
   {
      manifestName = manifestPath.substr(findFileExtension + 1);
   }
   else
   {
      manifestName = manifestPath;
   }
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
      std::cout << "ERROR: Unable to open " << path << ".\n";
   }
}

Ship::Ship(const Ship& other) {
   manifestName = other.manifestName;
   manifestPath = other.manifestPath;

   for(int i = 0; i < 8; i++) 
   {
      for(int j = 0; j < 12; j++) 
      {
         bay[i][j] = other.bay[i][j];
      }
   }

   for(int i = 0; i < 4; i++) 
   {
      for(int j = 0; j < 24; j++) 
      {
         buffer[i][j] = other.buffer[i][j];
      }
   }

   balanceChild = other.balanceChild;
   onCrane = other.onCrane;
   craneLocation = other.craneLocation;
   h = other.h;
   depth = other.depth;
   fn = other.fn;
}


short Container::getDepth(Ship &ship)
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
         // for (int i = row; i < 8; i++)
         {
            if (ship.bay[i][column - 1].name != "UNUSED")
            {
               depth++;
            }
            else
            {
               break;
            }
         }
         return depth;
      }
   }
   catch (const std::exception &e)
   {
      std::cout << "Caught an exception: " << e.what() << "\n";
   }
   return -1;
}

bool Container::isContainer()
{
   return name != "NAN" && name != "UNUSED";
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

Ship& Ship::operator=(const Ship& other) {
   if (this != &other) 
   {
      manifestName = other.manifestName;
      manifestPath = other.manifestPath;

      for(int i = 0; i < 8; i++) 
      {
         for(int j = 0; j < 12; j++) 
         {
            bay[i][j] = other.bay[i][j];
         }
      }

      //copy the contents of the buffer
      for(int i = 0; i < 4; i++) 
      {
         for(int j = 0; j < 24; j++) 
         {
            buffer[i][j] = other.buffer[i][j];
         }
      }

      balanceChild = other.balanceChild;
      onCrane = other.onCrane;
      craneLocation = other.craneLocation;
      h = other.h;
      depth = other.depth;
      fn = other.fn;
   }

   return *this;
}

Container& Container::operator=(const Container& other) 
{
   if (this != &other) 
   {
      row = other.row;
      column = other.column;
      weight = other.weight;
      name = other.name;
   }
   return *this;
}

/*
int main(int argc, char *argv[])
{
   std::string manifestName;
   std::cout << "Input a manifest name: ";
   std::getline(std::cin, manifestName);
   std::cout << '\n';
   Ship currentShip(manifestName);
   Container *currentContainer;
   for (int i = 7; i >= 0; i--)
   {
      for (int j = 0; j < 12; j++)
      {
         std::cout << currentShip.bay[i][j].name[0] << ' ';
      }
      std::cout << '\n';
   }

//   for (int i = 7; i >= 0; i--)
//   {
//      for (int j = 0; j < 12; j++)
//      {
//         if (currentShip.bay[i][j].name != "NAN" && currentShip.bay[i][j].name != "UNUSED")
//         {
//            currentContainer = &currentShip.bay[i][j];
//            std::cout << "Depth of " << currentContainer->name << ": " << currentContainer->getDepth(currentShip) << '\n';
//         }
//      }
//   }
//   std::cout << "Port weight: " << currentShip.getPortWeight() << '\n';
//   std::cout << "Starboard weight: " << currentShip.getStarbordWeight() << '\n';
//   std::cout << "Number of Containers on ship: " << currentShip.getNumContainers() << '\n';
   return 0;
}
*/
