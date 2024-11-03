#ifndef STEEPESTASCENT_H
#define STEEPESTASCENT_H

#include "LocalSearch.h"

class SteepestAscent : public LocalSearch {
private:
    std::vector<std::tuple<Cube, int, int, int>> neighborValues;

public:
    // Constructor
    SteepestAscent(Cube init);

    void Algorithm();
};

#endif