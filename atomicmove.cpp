
#include "atomicmove.h"

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
