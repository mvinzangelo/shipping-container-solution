#ifndef ATOMICMOVE_H
#define ATOMICMOVE_H
#include "manifest/manifest.h"
#include "logfile/logfile.h"

class AtomicMove
{
public:
    AtomicMove();
    Ship *shipState;
    int timeToMove;
    std::string containerToMove;
    std::string locationToMove;
    int curr_i; // current location
    int curr_j;
    int target_i; // target location
    int target_j;
    bool isOffloaded; // from ship to truck
    bool isOnloaded;  // from truck to ship
};

#endif // ATOMICMOVE_H
