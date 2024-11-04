#ifndef RANDOMRESTART_H
#define RANDOMRESTART_H

#include "LocalSearch.h"
#include "SteepestAscent.h"

class RandomRestart : public LocalSearch {
private:
    int maxRestarts;
    int maxIterationsPerRestart;
    // std::vector<std::tuple<Cube, int, int, int>> neighborValues;
    std::vector<int> iterationsPerRestart;
    int bestObjectiveValue;
    Cube bestState;

public:
    RandomRestart(Cube init, int maxRestarts);

    void hillClimbingIteration(int maxIterations); 
    void Algorithm();

    std::vector<int> getIterationsPerRestart() const { return iterationsPerRestart; }
    int getTotalRestarts() const { return maxRestarts; }
};

#endif