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
};

#endif // ATOMICMOVE_H
