#ifndef ATOMICMOVE_H
#define ATOMICMOVE_H
#include "manifest/manifest.h"
#include "logfile/logfile.h"

class AtomicMove
{
public:
    AtomicMove();
    AtomicMove(Ship* ship, std::string containerToMove, int curr_i, int curr_j, int target_i, int target_j);
    Ship *shipState;
    int timeToMove;
    std::string containerToMove; //name of container
    std::string locationToMove; // cords
    int curr_i; // current location
    int curr_j;
    int target_i; // target location truck = -1, -1
    int target_j;
    bool isOffloaded; // from ship to truck
    bool isOnloaded;  // from truck to ship
};
#endif // ATOMICMOVE_H
