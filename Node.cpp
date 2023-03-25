#include "Node.h"

int calculateDistance(orderedPair point1, orderedPair point2);

//--------------- Node Class --------------------

Node::Node(){};
Node::Node(Ship ship)
{
    this->ship = ship;
    crain.first = 8;
    crain.second = 0;
    pinkBox.first = 8;
    pinkBox.second = 0;
    inShip = true;
    inBuffer = false;
    Fx = 0;
    Gx = 0;
    containersON.clear();
    containersOFF.clear();
    parent = nullptr;
};

Node::Node(Ship ship, std::vector<Container*> ON, std::vector<Container*> OFF)
{
    this->ship = ship;
    crain.first = 8;
    crain.second = 0;
    pinkBox.first = 8;
    pinkBox.second = 0;
    inShip = true;
    inBuffer = false;
    Fx = 0;
    Gx = 0;
    containersON = ON;
    containersOFF = OFF;
    parent = nullptr;
}

Node::Node(Node& curNode){
    this->ship = curNode.ship;
    this->crain = curNode.crain;
    this->pinkBox = curNode.pinkBox;
    inBuffer = curNode.inBuffer;
    Fx = curNode.Fx;
    Gx = curNode.Gx;
    parent = &curNode;
    containersOFF = curNode.containersOFF;
    containersON = curNode.containersON;
}

bool Node::GoalTest()
{
    if(containersOFF.empty() && containersON.empty())
    {
        return true;
    }
    else { return false; }
}

// std::vector<orderedPair> Node::findMatchingContainers()
// {
//     int bayWidth = 12;
//     int bayHeight = 8;
//     std::vector<orderedPair> matchingContainers;
//     for(int i = 0; i < this->containersOFF.size(); i++){
//         for(int y = 0; y < bayHeight; y++ )
//         {
//             for(int x = 0; x < bayWidth; x++)
//             {
//                 if(ship.bay[y][x].name == containersOFF[i]->name){ matchingContainers.push_back(orderedPair(y,x)); }
//             }
//         }
//     }
//     return matchingContainers;

// };

std::vector<int> Node::findTargetColumns()
{
    std::vector<int> targetColumns;
    for(int x = 0; x < 12; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            for(int i = 0; i < containersOFF.size(); i++)
            {
                if(ship.bay[y][x].name == containersOFF[i]->name)
                { 
                    targetColumns.push_back(x); 
                    i = containersOFF.size();
                    y = 8;
                }
                if(ship.bay[y][x].name == "UNUSED")
                {
                    i = containersOFF.size();
                    y = 8;
                }
            }
        }
    }
    return targetColumns;
}

std::vector<Container*> Node::findTop(std::vector<int> columns){
    std::vector<int> targetColumns = columns;
    std::vector<Container*> targetTops;
    for(int x = 0; x < targetColumns.size(); x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(ship.bay[y][targetColumns[x]].name == "UNUSED")
            {
                targetTops.push_back(&ship.bay[std::max(0,y -1)][targetColumns[x]]);
                y = 8;
            }
        }
    }
    for(int i = 0; i < targetTops.size(); i++)
    {
        std::cout << "[" << targetTops[i]->row -1 << ", " << targetTops[i]->column -1 <<"]\n";
    }
    return targetTops;
}

// void Node::checkTops()
// {
//     std::vector<Container*> targetTops = findTargetTops();
//     for(int i = 0; i < targetTops.size(); i++)
//     {
//         for(int j = 0; j < containersOFF.size(); j++)
//         {
//             if(targetTops[i]->name == containersOFF[j]->name)
//             {

//             }
//         }
//     }
// }

void Node::moveContainer(orderedPair Loc)
{
    bool Target = false;
    std::vector<int> targetColumns = findTargetColumns();
    std::vector<int> freeColumns;
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < targetColumns.size(); j++ )
        {
            if(targetColumns[j] == i){ Target = true; }
        }
        if(!Target){ freeColumns.push_back(i); }
        else Target = false;
    }
    if(freeColumns.empty())
    {

    }
    else
    {
        std::vector<Container*> freeTops = findTop(freeColumns);
        int minDist = 999;
        int tempDist;
        Container* closestSpot;
        for(int i = 0; i < freeTops.size(); i++)
        {
            tempDist = calculateDistance(Loc, orderedPair(freeTops[i]->row, freeTops[i]->column -1));
            if(tempDist < minDist)
            {
                minDist = tempDist;
                closestSpot = freeTops[i];
            }
        }
        ship.bay[closestSpot->row][closestSpot->column -1].name = ship.bay[Loc.first][Loc.second].name;
        ship.bay[closestSpot->row][closestSpot->column -1].weight = ship.bay[Loc.first][Loc.second].weight;
        ship.bay[Loc.first][Loc.second].name = "UNUSED";
        ship.bay[Loc.first][Loc.second].weight = 0;
        Fx += calculateDistance(crain, Loc) + minDist;
        crain.first = closestSpot->row-1;
        crain.second = closestSpot->column-1;
    }
}

// orderedPair Node::findOffboardTarget(std::string target)
// {
//     orderedPair targetLoc;
//     std::vector<orderedPair> matchingContainers = this->findMatchingContainers();

//     return targetLoc;
// };

// bool Node::isMoveable(orderedPair container)
// {
//     if(ship.bay[container.first + 1][container.second].name == "UNUSED"){ return true; }
//     else{ return false; } 
// }

void Node::offLoad(orderedPair container)
{
   Fx += offloadCost(container); 
   ship.bay[container.first][container.second].name = "UNUSED";
   ship.bay[container.first][container.second].weight = 0;
   inShip = false;
   inBuffer = true;
}

int Node::offloadCost(orderedPair container)
{
    int cost = 0;
    cost += calculateDistance(crain, container) + calculateDistance(container, pinkBox);
    std::cout << "off load cost: " << cost << std::endl;
    return cost;
}

void Node::print()
{
    ship.printShip();
    std::cout << "Fx : " << Fx 
              << "\nGx : " << Gx
              << "\nCrain: [" << crain.first << ", " << crain.second << "]\n"
              << "Pink: [" << pinkBox.first << ", " << pinkBox.second << "]\n"
              << "Containers OFF: " << containersOFF.empty() << std::endl
              << "Containers ON: " << containersON.empty() << std::endl;
}


// -------------- Helper functions --------------------------

orderedPair::orderedPair()
{
    first = 0;
    second = 0;
};

orderedPair::orderedPair(int y, int x)
{
     first = y;
     second = x;
};

void orderedPair::print()
{
    std::cout << "[" << first << ", " << second << "]";
}



int calculateDistance(orderedPair point1, orderedPair point2)
{
    return (abs(point1.first - point2.first) + abs(point1.second - point2.second));
};


