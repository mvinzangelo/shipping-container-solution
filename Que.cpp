  #include "Que.h"


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
                    std::cout << "Offloading : " << tempNode->ship.bay[targetTops[i]->row][targetTops[i]->column].name;
                    tempNode->containerMoved = tempNode->ship.bay[targetTops[i]->row][targetTops[i]->column].name;
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













// void Que::expand()
// {
//     Node* currentNode, *tempNode;
//     std::vector<orderedPair> currentLocations;


//     // Find columns with target containers
//     currentNode = heap.top();
//     currentLocations = currentNode->findMatchingContainers();
//     std::cout << "Locations for expand: \n";
//     for(int i = currentLocations.size() - 1; i >= 0; i--)
//     {
//         currentLocations[i].print();
//         if(currentNode->isMoveable(currentLocations[i])){
//             std::cout << " is movable\n";
//             tempNode = new Node(*currentNode);
//             tempNode->offLoad(currentLocations[i]);
//             tempNode->print();
//             heap.push(tempNode);
//             currentLocations.pop_back();
//             // if(!tempNode.isVisited())
//             // {
//             //     heap.push(tempNode);
//             // }
//         }
//         else{ std::cout << " is not movable\n"; }
        
//     }
//     std::cout << "locations left: \n";
//         for(int i = 0; i < currentLocations.size(); i++)
//         {
//             std::cout << "[" << currentLocations[i].first << ", " << currentLocations[i].second << "]\n"; 
//         }


// }

