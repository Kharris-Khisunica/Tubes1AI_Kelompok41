#ifndef STOCHASTICHC_H
#define STOCHASTICHC_H

#include "LocalSearch.h"
#include <random>

class Stochastic : public LocalSearch {
private:
    // std::vector<std::tuple<Cube, int, int, int>> neighborValues;
    std::random_device rd;
    std::mt19937 gen;
    int maxIterations;

public:
    // Constructor
    Stochastic(Cube init, int maxIter);

    // void generateAllNeighbors() override;
    std::tuple<Cube, int, int, int> selectRandomNeighbor();
    void Algorithm();
};

#endif