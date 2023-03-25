//#include "manifest/manifest.h"
//#include "Node.h"
#include "Que.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cstdlib>


std::list<Node*> generalSearch(Ship&, std::vector<Container*>, std::vector<Container*>);
int costToOffboard(Ship&, std::string);
int findOffboardTarget(Ship& ship, std::string targetName);
std::vector<orderedPair> findTargetContainers(Ship ship, std::string targetName);
int calculateDistance(orderedPair point1, orderedPair point2);

int main(int argc, char *argv[])
{

   std::string manifestName1 = "Ships/ShipCase1.txt";
   std::string manifestName2 = "Ships/ShipCase2.txt";
   std::string manifestName3 = "Ships/ShipCase3.txt";
   std::string manifestName4 = "Ships/ShipCase4.txt";
   std::string manifestName5 = "Ships/ShipCase5.txt";
   std::string manifestName6 = "Ships/ShipCase6.txt";

   Ship ship1(manifestName1);
   Ship ship2(manifestName2);
   Ship ship3(manifestName3);
   Ship ship4(manifestName4);
   Ship ship5(manifestName5);
   Ship ship6 (manifestName6);

   std::cout << "Case 1\n";
   ship1.printShip();
   std::cout << "\n\n";
   std::cout << "Case 2\n";
   ship2.printShip();
   std::cout << "\n\n";
   std::cout << "Case 3\n";
   ship3.printShip();
   std::cout << "\n\n";
   std::cout << "Case 4\n";
   ship4.printShip();
   std::cout << "\n\nCase5\n";
   ship5.printShip();
   std::cout << "\n\nCase6\n";
   ship6.printShip();
   std::cout << "\n\n";

   std::string targetName = "Dog";
   std::vector<Container*> containersOffNames, containersOnNames;
   containersOffNames.push_back(new Container(-1, -1, 0, targetName));

    std::list<Node*> moves = generalSearch(ship6, containersOnNames, containersOffNames);

   return 0;
}

std::list<Node*> generalSearch(Ship& ship, std::vector<Container*> ON, std::vector<Container*> OFF)
{
    Node* currentState = new Node(ship, ON, OFF);
    Node* tempState;
    Que Q(currentState);
    bool answer = false;
    while(!answer){
        if(Q.heap.empty())
        { 
            std::cout <<"Fail\n" ;
            std::list<Node*> empty;
            return empty;
        }
        currentState = Q.heap.top();
        if(currentState->GoalTest())
        {
            std::cout << "success!!\n";
            answer = true;
        }
        Q.expand();
    }
    std::list<Node*> moves;
    while(currentState->parent!=nullptr)
    {
        moves.push_front(currentState);
        currentState = currentState->parent;
    }
        moves.push_front(currentState);
        int sz = moves.size();
    for(int i = 0; i < sz; i++)
    {
        moves.front()->print();
        moves.pop_front();
    }
    return moves;

}

 int findOffboardTarget(Ship& ship, std::string targetName){
        std::vector<orderedPair> targetContainers = findTargetContainers(ship, targetName);
        std::cout << "Matching Containers found at position: \n";
        orderedPair offboard(8,0);
        orderedPair minCostContainer; 
        int minCost, currentCost;
        minCost = 999;
        orderedPair crain(ship.crainY, ship.crainX);

        return 0;
   };

   std::vector<orderedPair> findTargetContainers(Ship ship, std::string targetName)
   {
     int bayWidth = 12;
        int bayHeight = 8;
        std::vector<orderedPair> matchingContainer;
        for(int y = 0; y < bayHeight; y++ )
        {
            for(int x = 0; x < bayWidth; x++)
            {

                if(ship.bay[y][x].name == targetName)
                {
                    matchingContainer.push_back(orderedPair(y,x));
                }
            }
        }
        return matchingContainer;

   }






