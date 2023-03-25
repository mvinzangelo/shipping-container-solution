#ifndef BALANCE_H
#define BALANCE_H
#include "../manifest/manifest.h"
using namespace std;
#include <vector>
#include <queue> 
#include <cstdlib>
#include <unordered_set>

 
//FUNCTION STUBS
//stub for heuristic 
int balanceH(Ship currShip);
//lambda key for sorting q of nodes in search
auto sortRuleLambda = [] (Ship const& s1, Ship const& s2) -> bool
{
    return ( (s1.h + s1.depth) < (s2.h + s2.depth)) ;
};
//stub to print ship 
void printShip(Ship currShip);
//stub for balance check 
bool shipBalanced(Ship currShip); 


//returns container that was picked up from ship
Container pickUp(Ship currShip, int row, int col){

    //temp variable to hold container being picked up 
    Container temp = currShip.bay[row][col]; 

    return temp; 
}; 
//dropping off container operator 
void dropOff(Ship& currShip, Container& cont,int row, int col){

    //update container's specific location
    cont.row = row+1;
    cont.column = col+1; 
    
    //update currentShip with the new dropped off container
    currShip.bay[row][col] = cont; 
    currShip.bay[row][col].name = cont.name; 
    currShip.bay[row][col].weight = cont.weight; 

    //reset value of the onCrane after dropping off 
    Container temp; 
    currShip.onCrane = temp; 

    currShip.craneLocation = col; 

};
//update the newShips' bay to reflect what container was picked up
//and no longer in the same cell 
void removeContainer(Ship& newShip, int row, int col){

    newShip.bay[row][col].name = "UNUSED";
    newShip.bay[row][col].weight = 00000;  
}


//function for creating string hashID from a current ship for tackling already visited nodes 
string hashID(Ship& currShip){

    string hashString = std::to_string(currShip.craneLocation); //will hold the created string ID

    for(int i = 0; i < 12; ++i){
        for(int j = 0; j < 8; ++j){

            hashString += (currShip.bay[i][j].name);


        }
    }

    return hashString;

};//end generator for creating unique hash ID 

//expand the current ship's children by checking what operators can 
//be done and creating new children 
//actionType represents wheter we are picking up or dropping off
//even -> dropping off 
//odd -> picking up 
void operators(Ship& currShip, unordered_set<std::size_t>& visited,std::size_t& stringHash ,int actionType ){               

    //case where we are picking up a container to move 
    if(actionType % 2 != 0){
        
        for(int j = 0; j < 12; ++j ){

            for(int i = 7; i >= 0; --i){

                if(currShip.bay[i][j].name != "UNUSED" && currShip.bay[i][j].name != "NAN" ){
                    Ship newShip(currShip);
                    newShip.balanceChild.clear(); //clear children for newly created Ship 

                    newShip.onCrane = pickUp(currShip,i,j); 
                    std::cout<<"Pikcing up container: "<< newShip.bay[i][j].name << endl; 
                    //remove the current picked up crane for the currentShip
                    removeContainer(newShip,i,j); 

                    newShip.craneLocation = j;
            
                    //check using hash to if node already visited 
                    if(visited.find(stringHash) == visited.end()){ //hash value seen. meaning node already visite de
                        std::cout<<"Visited State!" << endl;
                    }
                    else{
                        visited.insert(stringHash); 
                        newShip.depth =newShip.depth + 1; 
                        currShip.balanceChild.push_back(newShip);
                    }

                    break; //exit loop to move on to next column in ship 
                }//search columns top to bottom to find first one we can pick up  

            }//go through rows 
             
        }//go through columns

        

    }//end if that picks up containers  


    //case where we are dropping off a container  
    if(actionType % 2 == 0 ){
 

         for(int j = 0; j < 12; ++j ){

            if(currShip.craneLocation != j){

                for(int i = 0; i < 8; ++i){

                    if(currShip.bay[i][j].name == "UNUSED"){
                        Ship newShip(currShip);
                        newShip.balanceChild.clear(); //clear children for newly created Ship 

                        dropOff(newShip,newShip.onCrane,i,j);
                        if(newShip.bay[i][j].name != "UNUSED" && newShip.bay[i][j].name != "NAN") 
                        {
                            std::cout<<"Dropping off container: "<< newShip.bay[i][j].name << endl;
                        }
                    
                        //check using hash if node already visited or not 
                       if(visited.find(stringHash) == visited.end()){ //hash value seen. meaning node already visite de
                            std::cout<<"Visited State!" << endl;
                        }
                        else{
                            visited.insert(stringHash); 
                            newShip.depth =newShip.depth + 1; 
                            currShip.balanceChild.push_back(newShip);
                        }

                        break; //don't need to check remaining rows above 
                        
                    }//first spot we may drop off the container

                }//go through rows 

            }//ensure that the location we are checking to drop off is not the one we just picked up from

        }//go through columns

    }//end if


};//end operators 



//general search function that will search through possible cases 
//to find best moves 


void balanceSearch(Ship& currShip, int qFunc){

int expandedNodes = 0;
int maxQ = 0;
int tempQ = 0; 

//queue of nodes to search through
queue<Ship> nodes; 


std::hash<std::string> hasher; //hash function object
unordered_set<std::size_t> visited; //unordered set to store seen hashes (i.e visited nodes)

//variable to hold store the current ship layout before expanding 
Ship currNode = currShip; 

//push initial ship into queue of ships to expand 
nodes.push(currNode); 
tempQ += 1; 
maxQ+= 1; 

//put initial board as visited for inital check 
//incase ship comes into port already legally balanced 
//visited.insert(currNode);


if(shipBalanced(currNode)){

    std::cout << "Ship already balanced!" << endl;
    std::cout << "Port weight: " << currNode.getPortWeight() << '\n';
    std::cout << "Starboard weight: " << currNode.getStarbordWeight() << '\n';
    std::cout << "Number of Containers on ship: " << currNode.getNumContainers() << '\n'; 
}//end if 


//main loop to find balance
while(!shipBalanced(currNode)){ //TODO: ADD HEURISTIC VALUE 

    //check if q is empty, in which case the search failed or no solution (hopefully the no solution) 
    if(nodes.size() == 0){
        std::cout<< "Failure: No valid solution :( (AKA. this boy buggin)" << endl;
        return; 
    }//

    //set heruistic value for the node 
    currNode.h = balanceH(currNode); 

    //sort the queue of nodes depending on the f(n) cost 
    //std::sort(nodes.front(),nodes.back(), sortRuleLambda); FIXME
    //std::sort(nodes.top(), nodes.back()); 



    //gets the current node from the q
    currNode = nodes.front();
    nodes.pop();
    tempQ --;
    expandedNodes++; 


    //insert currNode into visited 
    string tempID = hashID(currNode);
    std::size_t stringHash = hasher(tempID);
    visited.insert(stringHash);

    //check if currNode is balanced 
    if(shipBalanced(currNode)){

        std::cout << "Ship already balanced!" << endl;
        std::cout << "Port weight: " << currNode.getPortWeight() << '\n';
        std::cout << "Starboard weight: " << currNode.getStarbordWeight() << '\n';
        std::cout << "Number of Containers on ship: " << currNode.getNumContainers() << '\n';
        printShip(currNode); 
        return; 

    }//end if 

    

    if(currNode.onCrane.name != "NAN"){ //container on crane. dropping off 

        operators(currNode,visited,stringHash,2); 
    }

    else{//no container on crane, picking up container 
        operators(currNode,visited,stringHash,1);
        printShip(currNode);
        std::cout << "Port weight: " << currNode.getPortWeight() << '\n';
        std::cout << "Starboard weight: " << currNode.getStarbordWeight() << '\n'; 

    }
    

    for(int i = 0; i < currNode.balanceChild.size(); ++i)
    {
        nodes.push((currNode.balanceChild.at(i)));
        tempQ++;

    }//pushes all the newly created children into the q of nodes

};// main while loop 



}//end balanceSearch; 



//function that checks if ship is legally balanced 
bool shipBalanced(Ship currShip){

    float portW = currShip.getPortWeight();
    float starboardW = currShip.getStarbordWeight(); 

    float p = (abs(portW - starboardW)) / max(portW,starboardW); 

    if( (p*100) <=10 ) { return true;}

    else{return false;};

}; 

void printShip(Ship currShip){

    for (int i = 7; i >= 0; i--)
   {
      for (int j = 0; j < 12; j++)
      {
         std::cout << currShip.bay[i][j].name[0] << ' ';
      }//end inner 
      std::cout << '\n';
   }//end outer

};//end printShip



int balanceH(Ship currShip){

    int moveCount = 0; //minimum number of containers to achieve balance 

    vector<int>contW; //containerWeights to be stored to determine which weights are best to move 
    float portW = currShip.getPortWeight();
    float starboardW = currShip.getStarbordWeight(); 

    //check which weights we want to move(which side is heaver)
    float temp = min(portW,starboardW); 

    if(temp == portW){//arrange left side containers into vector 
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                contW.push_back(currShip.bay[i][j].weight);
            }
        }

    }

    else if (temp == starboardW){//arrange right side containers into vector

        for (int i = 0; i < 8; i++)
        {
            for (int j = 6; j < 12; j++)
            {
                contW.push_back(currShip.bay[i][j].weight);
            }
        }

    }


    sort(contW.begin(),contW.end(),greater<int>()); //sort vector list in descending order 

    float balanceMass = (portW + starboardW) / 2; //never changes for ship 
    float deficit = balanceMass - min(portW,starboardW); 


    for(int i = 0; i < contW.size(); ++i)
    {
        if(contW.at(i) <= deficit)
        {
            moveCount++; 
        }
    }

    return moveCount; 

}//end heuristic func





#endif 


