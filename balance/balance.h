#ifndef BALANCE_H
#define BALANCE_H

#include "../manifest/manifest.h"

//OPERATORS  

//returns container that was picked up from ship
Container pickUp(Ship& currShip, int row, int col){

    //temp variable to hold container being picked up 
    Container temp = currShip.bay[row][col]; 

    //update slot where old container was to be empty
    currShip.bay[row][col].name = "UNUSED";
    currShip.bay[row][col].weight = 00000;  

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

};



//expand the current ship's children by checking what operators can 
//be done and creating new children 
void operators(Ship visited[] ){


};//end operators 

#endif 