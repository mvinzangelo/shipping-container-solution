#ifndef BALANCE_H
#define BALANCE_H
#include "../manifest/manifest.h"
using namespace std;
#include <vector>
#include <queue> 
#include <set> 


//OPERATORS  


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
void operators(Ship& currShip, set<Ship> visited, int actionType ){

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
                        std::cout<<"Dropping off container: "<< newShip.bay[i][j].name << endl;

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

/*
void balanceSearch(Ship& currShip, int qFunc){

int expandedNodes = 0;
int maxQ = 0;
int tempQ = 0; 

//queue of nodes to search through
queue<Ship> nodes; 

//list of nodes already visited CHANGED FROM VECTOR TO SET
set<Ship> visited; 

//variable to hold store the current ship layout before expanding 
Ship currNode = currShip; 

//push initial ship into queue of ships to expand 
nodes.push(currNode); 
tempQ += 1; 
maxQ+= 1; 

//put initial board as visited for inital check 
//incase ship comes into port already legally balanced 
visited.push_back(currNode);





}; 

*/
#endif 


