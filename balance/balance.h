#ifndef BALANCE_H
#define BALANCE_H
#include "../manifest/manifest.h"
using namespace std;
#include <vector>
#include <queue> 
#include <cstdlib>

//OPERATORS  

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


//expand the current ship's children by checking what operators can 
//be done and creating new children 
//actionType represents wheter we are picking up or dropping off
//even -> dropping off 
//odd -> picking up 
void operators(Ship& currShip, vector<Ship> visited, int actionType ){

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
                    
                    //check wheter newly created ship has been visited already 
                    bool inVisited = false;
                    for(auto const &item: visited)
                    {
                        if(item == newShip){inVisited = true; break;}

                    }//check whether newShip has already been visited 

                    if(!inVisited){
                        newShip.depth =newShip.depth + 1; 
                        currShip.balanceChild.push_back(newShip); 
                        

                    }//new node created,update children of parent and increase depth of search 

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
                        

                        //check wheter newly created ship has been visited already 
                        bool inVisited = false;
                        for(auto const &item: visited)
                        {
                            if(item == newShip){inVisited = true; break;}

                        }//check whether newShip has already been visited 

                        if(!inVisited){
                            newShip.depth = newShip.depth + 1;
                            currShip.balanceChild.push_back(newShip); 
                             

                        }//new node created,update children of parent and increase depth of search 

                        

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

//list of nodes already visited CHANGED FROM VECTOR TO SET
vector<Ship>visited; 

//variable to hold store the current ship layout before expanding 
Ship currNode = currShip; 

//push initial ship into queue of ships to expand 
nodes.push(currNode); 
tempQ += 1; 
maxQ+= 1; 

//put initial board as visited for inital check 
//incase ship comes into port already legally balanced 
visited.push_back(currNode);


if(shipBalanced(currNode)){

    std::cout << "Ship already balanced!" << endl;
    std::cout << "Port weight: " << currNode.getPortWeight() << '\n';
    std::cout << "Starboard weight: " << currNode.getStarbordWeight() << '\n';
    std::cout << "Number of Containers on ship: " << currNode.getNumContainers() << '\n'; 
}//end if 


//actionType represents wheter we are picking up or dropping off
//even -> dropping off 
//odd -> picking up 
int actionType = 1; 

//count variable to determine when to change our actionType
//depending on the amount of children created 
int newLayer = 0; 

//main loop to find balance
while(!shipBalanced(currNode)){

    if(nodes.size() == 0){
        std::cout<< "Failure: No valid solution :( (AKA. this boy buggin)" << endl;
    }//i


    //TODO: Add heuristic value for currShip.h after breadth first search works 

    //get first element from queue and pop 
    currNode = nodes.front();   

    nodes.pop(); 

    tempQ -=1;
    expandedNodes +=1; 


    //visited.push_back(currNode);   
    printShip(currNode); 

    if(shipBalanced(currNode)){

        std::cout << "Ship already balanced!" << endl;
        std::cout << "Port weight: " << currNode.getPortWeight() << '\n';
        std::cout << "Starboard weight: " << currNode.getStarbordWeight() << '\n';
        std::cout << "Number of Containers on ship: " << currNode.getNumContainers() << '\n';
        printShip(currNode); 

    }//end if 


    operators(currNode,visited,actionType); 
    actionType ++; //increment to switch between picking up and dropping off 
    visited.push_back(currNode); 

    //for loop to iterate through possibly made children
    //updating heuristic value and appending 
    //newly created child to queue for further expansion 
    for(int i=0; i < currNode.balanceChild.size(); ++i){

        nodes.push(currNode.balanceChild.at(i)); //future node to expand 
        tempQ += 1;

    }//end for 

    if(tempQ > maxQ){maxQ = tempQ;} //end if for updating max q size 




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


#endif 


