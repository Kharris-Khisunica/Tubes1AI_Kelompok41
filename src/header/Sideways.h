#ifndef SIDEWAYS_H
#define SIDEWAYS_H

#include "LocalSearch.h"
#include <vector>
#include <tuple>

class Sideways : public LocalSearch {
private:
    std::vector<std::tuple<Cube, int, int, int>> neighborValues;
    int sidewaysMoveLimit;  

public:
    Sideways(Cube init, int sidewaysLimit);

    void generateAllNeighbors() override;

    void Algorithm();
};

#endif
