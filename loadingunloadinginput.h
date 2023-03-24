#ifndef LOADINGUNLOADINGINPUT_H
#define LOADINGUNLOADINGINPUT_H

#include <vector>
#include "manifest/manifest.h"

enum INPUT_TYPE
{
    LOADING,
    UNLOADING
};

class LoadingUnloadingInput
{
public:
    LoadingUnloadingInput();
    INPUT_TYPE currInputType;
    std::vector<Container *> loadContainers;
    std::vector<Container *> unloadContainers;

private:
};

#endif // LOADINGUNLOADINGINPUT_H
