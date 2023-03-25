#include "balance.h"
#include "../manifest/manifest.h"

// returns container that was picked up from ship
Container pickUp(Ship currShip, int row, int col, int bayOrBuffer)
{ // 1: bay, 0: buffer

    Container temp;
    // temp variable to hold container being picked up
    if (bayOrBuffer == 1)
    {
        temp = currShip.bay[row][col];
    }
    else if (bayOrBuffer == 0)
    {
        temp = currShip.buffer[row][col];
    }

    return temp;
};

void dropOff(Ship &currShip, Container &cont, int row, int col, int bayOrBuffer)
{ // 1: bay, 0: buffer

    // update container's specific location
    cont.row = row + 1;
    cont.column = col + 1;

    if (bayOrBuffer == 1)
    {
        // update currentShip with the new dropped off container
        currShip.bay[row][col] = cont;
        currShip.bay[row][col].name = cont.name;
        currShip.bay[row][col].weight = cont.weight;
    }

    else if (bayOrBuffer == 0)
    {
        // update currentShip with the new dropped off container
        currShip.buffer[row][col] = cont;
        currShip.buffer[row][col].name = cont.name;
        currShip.buffer[row][col].weight = cont.weight;
    }

    // reset value of the onCrane after dropping off
    Container temp;
    currShip.onCrane = temp;

    currShip.craneLocation = col;
};

// update the newShips' bay to reflect what container was picked up
// and no longer in the same cell
void removeContainer(Ship &newShip, int row, int col, int bayOrBuffer)
{ // 1: bay, 0:buffer
    if (bayOrBuffer == 1)
    {
        newShip.bay[row][col].name = "UNUSED";
        newShip.bay[row][col].weight = 00000;
    }

    else if (bayOrBuffer == 0)
    {
        newShip.buffer[row][col].name = "UNUSED";
        newShip.buffer[row][col].weight = 00000;
    }
};

// function for creating string hashID from a current ship for tackling already visited nodes
string hashID(Ship &currShip)
{

    string hashString = std::to_string(currShip.craneLocation); // will hold the created string ID

    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {

            hashString += (currShip.bay[i][j].name);
        }
    }

    return hashString;

}; // end generator for creating unique hash ID

// function to check if ship can be balanced legally.
// will determine if we need to sift right away
bool balancePossible(vector<int> &weights)
{                                              // function credited to online resource
    std::sort(weights.begin(), weights.end()); // sort the list in non-decreasing order
    int n = weights.size();
    int total_sum = accumulate(weights.begin(), weights.end(), 0); // calculate the total sum of the list
    int left_sum = 0;
    for (int i = 0; i < n; i++)
    {
        left_sum += weights[i];
        int right_sum = total_sum - left_sum;
        double diff = abs(left_sum - right_sum) / (double)total_sum; // calculate the absolute difference as a fraction of the total sum
        if (diff <= 0.1)
        {
            return true;
        }
    }
    return false;
};

// helper function for balancePossible that stores all the weights into a vector of ints
vector<int> isolateContainerWeights(Ship &currShip)
{

    vector<int> temp; // return value for function

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (currShip.bay[i][j].name != "UNUSED" && currShip.bay[i][j].name != "NAN")
            {
                temp.push_back(currShip.bay[i][j].weight);
            } // end if to push weights into temp vector

        } // end inner for
    }     // end outer for

    return temp;
};

// SIFT function to SIFT balance the ship due to no legal balance
// SIFT here is operating under assumption buffer is empty prior to starting
vector<AtomicMove *> SIFT(Ship &currShip)
{
    // vector<Ship>atomicMove;
    vector<AtomicMove *> moves;

    vector<int> weights = isolateContainerWeights(currShip); // vector to hold container weights so we can sort prior to putting back on the ship
    sort(weights.begin(), weights.end(), greater<int>());    // sort vector from largest to smallest

    int bufferCol = 23; // bufferCol index
    int bufferRow = 0;  // bufferRow index

    // want to empty ship and place all containers into buffer
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            if (currShip.bay[i][j].name != "UNUSED" && currShip.bay[i][j].name != "NAN")
            {

                currShip.onCrane = pickUp(currShip, i, j, 1); // pick up crane to move (1:bay)
                removeContainer(currShip, i, j, 1);
                dropOff(currShip, currShip.onCrane, bufferRow, bufferCol, 0); // 0 means dropping off container in buffer
                bufferCol--;

                string newLocation = "{" + to_string(bufferRow) + "," + to_string(bufferCol) + "}";
                AtomicMove *currAtoimcMove = new AtomicMove();
                currAtoimcMove->containerToMove = currShip.onCrane.name;
                currAtoimcMove->locationToMove = newLocation;

                // keep track of each atomic move through vector of Ships
                Ship *tempShip = new Ship();
                tempShip = &currShip;
                printShip(*tempShip);
                std::cout << endl;
                currAtoimcMove->shipState = tempShip;

                // push created struct into atomicMove vector

                // atomicMove.push_back(temp);

            } // end if to unload the containers into the buffer
        }
    }
    // at this point, all containers are in buffer, begin inserting back into the ship from heaviest to lightest in
    // middle of the ship in following sequence: 6,7,5,8,4,9,3,10,2,11,1,12 (col number in bay of ship)

    vector<int> insertSeq{6, 7, 5, 8, 4, 9, 3, 10, 2, 11, 1, 12};
    for (int j = 23; j > 0; --j)
    {
        if (currShip.buffer[0][j].weight == weights.front())
        {                                                                     // found the heaviest weight in vector to move
            currShip.onCrane = pickUp(currShip, 0, j, 0);                     // 0 for picking up in buffer
            dropOff(currShip, currShip.onCrane, 0, insertSeq.front() - 1, 1); // drop off container into bay of currShip [denoted by the 1]
            removeContainer(currShip, 0, j, 0);

            // keep track of each atomic move through vector of Ships
            // Ship temp = currShip;
            // atomicMove.push_back(temp);

            string newLocation = "{" + to_string(0) + "," + to_string(insertSeq.front()) + "}";
            AtomicMove *currAtoimcMove = new AtomicMove();
            currAtoimcMove->containerToMove = currShip.onCrane.name;
            currAtoimcMove->locationToMove = newLocation;

            // keep track of each atomic move through vector of Ships
            Ship *tempShip = new Ship();
            tempShip = &currShip;
            printShip(*tempShip);
            std::cout << endl;
            currAtoimcMove->shipState = tempShip;

            // remove elements from vectors to contiue through iteration
            insertSeq.erase(insertSeq.begin());
            weights.erase(weights.begin());
        }
    }

    printShip(currShip); // print ship to see if output looks properly SIFTED
    return moves;        // return vector of atomicMoves
};

// expand the current ship's children by checking what operators can
// be done and creating new children
// actionType represents wheter we are picking up or dropping off
// even -> dropping off
// odd -> picking up
void operators(Ship &currShip, unordered_set<std::size_t> &visited, std::size_t &stringHash, int actionType)
{

    // case where we are picking up a container to move
    if (actionType % 2 != 0)
    {

        for (int j = 0; j < 12; ++j)
        {

            for (int i = 7; i >= 0; --i)
            {

                if (currShip.bay[i][j].name != "UNUSED" && currShip.bay[i][j].name != "NAN")
                {
                    Ship newShip(currShip);
                    newShip.balanceChild.clear(); // clear children for newly created Ship

                    newShip.onCrane = pickUp(currShip, i, j, 1); // 1 for picking up in bay
                    std::cout << "Pikcing up container: " << newShip.bay[i][j].name << endl;
                    // remove the current picked up crane for the currentShip
                    removeContainer(newShip, i, j, 1);

                    newShip.craneLocation = j;

                    // check using hash to if node already visited
                    if (visited.find(stringHash) == visited.end())
                    { // hash value seen. meaning node already visite de
                        std::cout << "Visited State!" << endl;
                    }
                    else
                    {
                        visited.insert(stringHash);
                        newShip.depth = newShip.depth + 1;
                        newShip.fn = newShip.h + newShip.depth;
                        currShip.balanceChild.push_back(newShip);
                    }

                    break; // exit loop to move on to next column in ship
                }          // search columns top to bottom to find first one we can pick up

            } // go through rows

        } // go through columns

    } // end if that picks up containers

    // case where we are dropping off a container
    if (actionType % 2 == 0)
    {

        for (int j = 0; j < 12; ++j)
        {

            if (currShip.craneLocation != j)
            {

                for (int i = 0; i < 8; ++i)
                {

                    if (currShip.bay[i][j].name == "UNUSED")
                    {
                        Ship newShip(currShip);
                        newShip.balanceChild.clear(); // clear children for newly created Ship

                        dropOff(newShip, newShip.onCrane, i, j, 1); // 1 means dropping off container in bay
                        if (newShip.bay[i][j].name != "UNUSED" && newShip.bay[i][j].name != "NAN")
                        {
                            std::cout << "Dropping off container: " << newShip.bay[i][j].name << endl;
                        }

                        // check using hash if node already visited or not
                        if (visited.find(stringHash) == visited.end())
                        { // hash value seen. meaning node already visite de
                            std::cout << "Visited State!" << endl;
                        }
                        else
                        {
                            visited.insert(stringHash);
                            newShip.depth = newShip.depth + 1;
                            newShip.fn = newShip.h + newShip.depth;
                            currShip.balanceChild.push_back(newShip);
                        }

                        break; // don't need to check remaining rows above

                    } // first spot we may drop off the container

                } // go through rows

            } // ensure that the location we are checking to drop off is not the one we just picked up from

        } // go through columns

    } // end if

}; // end operators

// general search function that will search through possible cases
// to find best moves. Returns a vector of atomicMoves for UI
vector<AtomicMove *> balanceSearch(Ship &currShip, int qFunc)
{

    // inital check to determine if the ship can be legally balanced
    vector<int> weights = isolateContainerWeights(currShip);
    bool canBalance = balancePossible(weights);

    vector<AtomicMove *> moves; // return vector for UI

    if (canBalance)
    {
        std::cout << "Can legally balance!" << endl;
    }
    else
    {
        std::cout << "Cannot legally balance. Using SIFT" << endl;
        moves = SIFT(currShip); // keep list of atomic moves to give frontEnd

        for (int i = 0; i < moves.size(); ++i)
        {
            std::cout << "New move" << endl;
            // printShip(atomicMoves->at(i).*shipsState); //print out each atomic move to console
            std::cout << endl;
        }
        return moves;
    }

    int expandedNodes = 0;
    int maxQ = 0;
    int tempQ = 0;

    // queue of nodes to search through CHANGING TO VECTOR FOR TEST
    // queue<Ship> nodes;
    // vector<Ship>nodes;
    queue<Ship> nodes;

    std::hash<std::string> hasher;      // hash function object
    unordered_set<std::size_t> visited; // unordered set to store seen hashes (i.e visited nodes)

    // variable to hold store the current ship layout before expanding
    Ship currNode = currShip;

    // push initial ship into queue of ships to expand
    nodes.push(currNode);
    // nodes.push_back(currNode);
    tempQ += 1;
    maxQ += 1;

    // put initial board as visited for inital check
    // incase ship comes into port already legally balanced
    // visited.insert(currNode);

    if (shipBalanced(currNode))
    {

        std::cout << "Ship already balanced!" << endl;
        std::cout << "Port weight: " << currNode.getPortWeight() << '\n';
        std::cout << "Starboard weight: " << currNode.getStarbordWeight() << '\n';
        std::cout << "Number of Containers on ship: " << currNode.getNumContainers() << '\n';
    } // end if

    // main loop to find balance
    while (!shipBalanced(currNode))
    { // TODO: ADD HEURISTIC VALUE

        // check if q is empty, in which case the search failed or no solution (hopefully the no solution)
        if (nodes.size() == 0)
        {
            std::cout << "Failure: No valid solution :( (AKA. this boy buggin)" << endl;
            return moves;
        } //

        // set heruistic value for the node
        currNode.h = balanceH(currNode);

        // sort the queue of nodes depending on the f(n) cost
        // std::sort(nodes.begin(),nodes.end(), [](Ship& lhs, Ship& rhs){return lhs.fn>rhs.fn;});

        // gets the current node from the q
        currNode = nodes.front();
        nodes.pop();
        // nodes.erase(nodes.begin()); when nodes if vector
        tempQ--;
        expandedNodes++;

        // insert currNode into visited
        string tempID = hashID(currNode);
        std::size_t stringHash = hasher(tempID);
        visited.insert(stringHash);

        // check if currNode is balanced
        if (shipBalanced(currNode))
        {

            printShip(currNode);
            std::cout << "Ship balanced!" << endl;
            std::cout << "Port weight: " << currNode.getPortWeight() << '\n';
            std::cout << "Starboard weight: " << currNode.getStarbordWeight() << '\n';
            std::cout << "Number of Containers on ship: " << currNode.getNumContainers() << '\n';
            return moves; // FIX ME (Add atomicMoves for regular balancing)

        } // end if

        if (currNode.onCrane.name != "NAN")
        { // container on crane. dropping off

            operators(currNode, visited, stringHash, 2);
            // currNode.fn = currNode.depth + currNode.h;
        }

        else
        { // no container on crane, picking up container
            operators(currNode, visited, stringHash, 1);
            // currNode.fn = currNode.depth + currNode.h;
            printShip(currNode);
            std::cout << "Port weight: " << currNode.getPortWeight() << '\n';
            std::cout << "Starboard weight: " << currNode.getStarbordWeight() << '\n';
        }

        for (int i = 0; i < currNode.balanceChild.size(); ++i)
        {
            nodes.push((currNode.balanceChild.at(i)));
            // nodes.push_back((currNode.balanceChild.at(i)));
            tempQ++;

        } // pushes all the newly created children into the q of nodes

    }; // main while loop

} // end balanceSearch;

// function that checks if ship is legally balanced
bool shipBalanced(Ship currShip)
{

    float portW = currShip.getPortWeight();
    float starboardW = currShip.getStarbordWeight();

    float p = (abs(portW - starboardW)) / max(portW, starboardW);

    if ((p * 100) <= 10)
    {
        return true;
    }

    else
    {
        return false;
    };
};

void printShip(Ship currShip)
{

    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 12; j++)
        {
            std::cout << currShip.bay[i][j].name[0] << ' ';
        } // end inner
        std::cout << '\n';
    } // end outer

}; // end printShip

int balanceH(Ship currShip)
{

    int moveCount;
    // check if container on ship, because then increase moveCount
    if (currShip.onCrane.name != "NAN")
    {
        moveCount = 1;
    }

    else
    {
        moveCount = 0;
    } // nothing on crane

    vector<int> contW; // containerWeights to be stored to determine which weights are best to move
    float portW = currShip.getPortWeight();
    float starboardW = currShip.getStarbordWeight();

    // check which weights we want to move(which side is heaver)
    float temp = max(portW, starboardW);

    if (temp == portW)
    { // arrange left side containers into vector
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                contW.push_back(currShip.bay[i][j].weight);
            }
        }
    }

    else if (temp == starboardW)
    { // arrange right side containers into vector

        for (int i = 0; i < 8; i++)
        {
            for (int j = 6; j < 12; j++)
            {
                contW.push_back(currShip.bay[i][j].weight);
            }
        }
    }

    sort(contW.begin(), contW.end(), greater<int>()); // sort vector list in descending order

    float balanceMass = (portW + starboardW) / 2; // never changes for ship
    float deficit = balanceMass - min(portW, starboardW);

    for (int i = 0; i < contW.size(); ++i)
    {
        if (contW.at(i) <= deficit && contW.at(i) != 0)
        {
            moveCount++;
        }
    }

    return moveCount; // moveCount represents minutes

} // end heuristic func
