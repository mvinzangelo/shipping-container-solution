#ifndef BALANCE_H
#define BALANCE_H
#include "../manifest/manifest.h"
using namespace std;
#include <vector>
#include <queue>
#include <cstdlib>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include "../atomicmove.h"

// FUNCTION STUBS

// stub for heuristic
int balanceH(Ship currShip);

// stub to print ship
void printShip(Ship currShip);
// stub for balance check
bool shipBalanced(Ship currShip);

// returns container that was picked up from ship
Container pickUp(Ship currShip, int row, int col, int bayOrBuffer); // 1: bay, 0: buffer

// dropping off container operator
void dropOff(Ship &currShip, Container &cont, int row, int col, int bayOrBuffer); // 1: bay, 0: buffer

// update the newShips' bay to reflect what container was picked up
// and no longer in the same cell
void removeContainer(Ship &newShip, int row, int col, int bayOrBuffer); // 1: bay, 0:buffer

// function for creating string hashID from a current ship for tackling already visited nodes
string hashID(Ship &currShip);

// function to check if ship can be balanced legally.
// will determine if we need to sift right away
bool balancePossible(vector<int> &weights); // function credited to online resource

// helper function for balancePossible that stores all the weights into a vector of ints
vector<int> isolateContainerWeights(Ship &currShip);

// SIFT function to SIFT balance the ship due to no legal balance
// SIFT here is operating under assumption buffer is empty prior to starting
vector<AtomicMove *> SIFT(Ship &currShip);

// expand the current ship's children by checking what operators can
// be done and creating new children
// actionType represents wheter we are picking up or dropping off
// even -> dropping off
// odd -> picking up
void operators(Ship &currShip, unordered_set<std::size_t> &visited, std::size_t &stringHash, int actionType);

// general search function that will search through possible cases
// to find best moves
vector<AtomicMove *> balanceSearch(Ship &currShip, int qFunc);

// function that checks if ship is legally balanced
bool shipBalanced(Ship currShip);

// print contents of ship
void printShip(Ship currShip);

// heuristic function
int balanceH(Ship currShip);

#endif
