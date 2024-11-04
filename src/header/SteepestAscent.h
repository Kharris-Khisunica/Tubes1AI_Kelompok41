#ifndef STEEPESTASCENT_H
#define STEEPESTASCENT_H

#include "LocalSearch.h"

class SteepestAscent : public LocalSearch {
public:
    // Constructor
    SteepestAscent(Cube init);

    void Algorithm();
};

#endif