#include "Node.h"

int calculateDistance(orderedPair point1, orderedPair point2);
std::vector<AtomicMove*> generalSearch(Ship& ship, std::vector<Container*> ON, std::vector<Container*> OFF);
int findOffboardTarget(Ship& ship, std::string targetName);
std::vector<orderedPair> findTargetContainers(Ship ship, std::string targetName);
int costToOffboard(Ship&, std::string);

AtomicMove::AtomicMove()
{

}

AtomicMove::AtomicMove(Ship* ship, std::string containerToMove, int curr_i, int curr_j, int target_i, int target_j)
{
    this->shipState = ship;
    this->containerToMove = containerToMove;
    locationToMove = "[" + std::to_string(curr_i) + "," + std::to_string(curr_j) + "]";
    this->curr_i = curr_i;
    this->curr_j = curr_j;
    this->target_i = target_i;
    this->target_j = target_j;
    if(target_i == -1){ isOffloaded = true; }
    else { isOffloaded = false; }
    if(curr_i == -1){ isOnloaded = true; }
    else { isOnloaded = false; }
};

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
    inTruck = false;
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
    inTruck = false;
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
    this->Fx = curNode.Fx;
    this->Gx = curNode.Gx;
    this->parent = &curNode;
    for(int i = 0 ; i < curNode.containersOFF.size(); i++)
    {
        this->containersOFF.push_back(curNode.containersOFF[i]);
    }
    std::cout << curNode.containersON.size() << '\n';
    for(int i = 0 ; i < curNode.containersON.size(); i++)
    {
        this->containersON.push_back(curNode.containersON[i]);
    }
       
}

bool Node::GoalTest()
{
    if(containersOFF.empty() && containersON.empty())
    {
        return true;
    }
    else { return false; }
}

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
    // for(int i = 0; i < targetTops.size(); i++)
    // {
    //     std::cout << "[" << targetTops[i]->row -1 << ", " << targetTops[i]->column -1 <<"]\n";
    // }
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

        std::cout << "Container moved too [" << closestSpot->row << ", " << closestSpot->column-1 <<"]\n";
        this->targetLoc.first = closestSpot->row;
        this->targetLoc.second = closestSpot->column -1;
        
        ship.bay[closestSpot->row][closestSpot->column -1].name = ship.bay[Loc.first][Loc.second].name;
        ship.bay[closestSpot->row][closestSpot->column -1].weight = ship.bay[Loc.first][Loc.second].weight;
        ship.bay[Loc.first][Loc.second].name = "UNUSED";
        ship.bay[Loc.first][Loc.second].weight = 0;
        Fx += calculateDistance(crain, Loc) + minDist;
        crain.first = closestSpot->row;
        crain.second = closestSpot->column-1;
        //inShip = true;
        //inBuffer = false;
    }
}

void Node::onboard(Container* container)
{
    std::cout << "onboarding " << container->name << '\n';
    bool Target = false;
    // find columns that don't have container that need to be offloaded
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
        // Find the top free spot of columns without conainers to be offloaded
        std::vector<Container*> freeTops = findTop(freeColumns);
        int minDist = 999;
        int tempDist;
        orderedPair tempLoc, closestSpot;
        //finds the closest spot to onboard container
        for(int i = 0; i <freeTops.size(); i++)
        {
            tempLoc.first = freeTops[i]->row;
            tempLoc.second = freeTops[i]->column -1;
            tempDist = calculateDistance(pinkBox,tempLoc);
            if(tempDist < minDist)
            {
                minDist = tempDist;
                closestSpot = tempLoc;
            }
        }
        Fx += minDist; //update cost;
        if(!inTruck){ Fx += 4;}
        inBuffer = false;
        inTruck = false;
        inShip = true;
        
        this->targetLoc.first = closestSpot.first +1;
        this->targetLoc.second = closestSpot.second;
        this->containerLoc.first = -1;
        this->containerLoc.second = -1;
        this->containerMoved = container->name;

        crain.first = closestSpot.first +1;//update crain
        crain.second = closestSpot.second;
        ship.bay[closestSpot.first][closestSpot.second].name = container->name; //update container
        ship.bay[closestSpot.first][closestSpot.second].weight = container->weight;
        std::cout << "container Onboard!\n";
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
   inBuffer = false;
   inTruck = true;
   crain.first = 8;
   crain.second = 0;
   std::string containerMoved;
   std::string targetLocation;
}

int Node::offloadCost(orderedPair container)
{
    int cost = 0;
    // moving to ship
    if(inBuffer){ cost = 4;} 
    else if(inTruck){ cost = 2; }
    cost += calculateDistance(crain, container) + calculateDistance(container, pinkBox) + 2;
    std::cout << "\noff load cost: " << cost << std::endl;
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

//-------------- Que class --------------------------------

Que::Que(Node* node)
{
    heap.push(node);
    visited.push_back(node);

};

void Que::push(Node* newNode)
{
    heap.push(newNode);
    visited.push_back(newNode);
}






void Que::expand()
{   bool match = false;
    Node* currentNode, *tempNode;
    currentNode = heap.top();
    heap.pop();
    //if the current Node has containers to still come off
    if(!currentNode->containersOFF.empty()){
        //finds the top of columns that have containers to be offboarded
        std::vector<Container*> targetTops = currentNode->findTop(currentNode->findTargetColumns()); 
        for(int i = 0; i < targetTops.size(); i++)
        {
            for(int j = 0; j < currentNode->containersOFF.size(); j++)
            {
                //Offboard container
                // if container on the top matches a one to be offboared
                // take if off
                if(targetTops[i]->name == currentNode->containersOFF[j]->name) 
                {
                    tempNode = new Node(*currentNode); //copy current node
                    tempNode->inBuffer = currentNode->inBuffer;
                    tempNode->inShip = currentNode->inShip;
                    tempNode->inTruck = currentNode->inTruck;

                    std::cout << "\nOffLoading [" << targetTops[i]->row - 1<< ", " << targetTops[i]->column - 1<< "]\n";
                    std::cout << "Offloading : " << tempNode->ship.bay[targetTops[i]->row -1][targetTops[i]->column -1].name;
                    tempNode->containerMoved = tempNode->ship.bay[targetTops[i]->row -1][targetTops[i]->column -1].name;
                    tempNode->containerLoc.first = targetTops[i]->row -1 ;
                    tempNode->containerLoc.second = targetTops[i]->column - 1;
                    tempNode->targetLoc.first = -1;
                    tempNode->targetLoc.second= -1;


                    tempNode->offLoad(orderedPair(targetTops[i]->row -1,targetTops[i]->column-1)); //offload target container
                    tempNode->containersOFF.erase(tempNode->containersOFF.begin()+j); //Remove target from offboarding list
                    heap.push(tempNode);
                    tempNode->print();
                    match = true; //signals the container matched with one in OFF
                }
                
            }
            //Move container
            //if the container at the top of a column didn't match any of the names in offboard
            if(!match)
            {
                tempNode = new Node(*currentNode);
                tempNode->inBuffer = currentNode->inBuffer;
                tempNode->inShip = currentNode->inShip;
                tempNode->inTruck = currentNode->inTruck;

                std::cout << "\nMoving container [" <<targetTops[i]->row -1 << ", " << targetTops[i]->column - 1 << "]\n";
                std::cout << "Moving " << tempNode->ship.bay[targetTops[i]->row][targetTops[i]->column].name << std::endl;
                tempNode->containerMoved = tempNode->ship.bay[targetTops[i]->row][targetTops[i]->column].name;
                tempNode->containerLoc.first = targetTops[i]->row -1 ;
                tempNode->containerLoc.second = targetTops[i]->column - 1;

                tempNode->moveContainer(orderedPair(targetTops[i]->row -1,targetTops[i]->column-1));
                heap.push(tempNode);
                tempNode->print();
            }
            else
            {
                match = false;
            }
        } 
    }
    //Onboard container
     if(!(currentNode->containersON.empty()))
     {
         tempNode = new Node(*currentNode);
         tempNode->onboard(tempNode->containersON.back());
         tempNode->containersON.pop_back();
         tempNode->print();
         //tempNode->containersON.pop_back();
         heap.push(tempNode);
     }
    
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

std::vector<AtomicMove*> generalSearch(Ship& ship, std::vector<Container*> ON, std::vector<Container*> OFF)
{
    Node* currentState = new Node(ship, ON, OFF);
    Node* tempState;
    Que Q(currentState);
    bool answer = false;
    while(!answer){
        if(Q.heap.empty())
        { 
            std::cout <<"Fail\n" ;
            std::vector<AtomicMove*> empty;
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
    std::vector<AtomicMove*> atomicMoves;
    while(currentState->parent!=nullptr)
    {
        moves.push_front(currentState);
        currentState = currentState->parent;
    }
        moves.push_front(currentState);
        int sz = moves.size();
    for(int i = 0; i < sz; i++)
    {
        atomicMoves.push_back(new AtomicMove(&moves.front()->ship,
                                             moves.front()->containerMoved,
                                             moves.front()->containerLoc.first,
                                             moves.front()->containerLoc.second,
                                             moves.front()->targetLoc.first,
                                             moves.front()->targetLoc.second));
        moves.pop_front();
    }
    return atomicMoves;

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