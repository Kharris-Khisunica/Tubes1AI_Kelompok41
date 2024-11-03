#include "../header/SteepestAscent.h"

// Constructor
SteepestAscent::SteepestAscent(Cube init) : LocalSearch(init) {}

void SteepestAscent::generateAllNeighbors() {
    neighborValues.clear();

    for (int x1 = 0; x1 < currentState.getSize(); ++x1) {
        for (int y1 = 0; y1 < currentState.getSize(); ++y1) {
            for (int z1 = 0; z1 < currentState.getSize(); ++z1) {
                for (int x2 = 0; x2 < currentState.getSize(); ++x2) {
                    for (int y2 = 0; y2 < currentState.getSize(); ++y2) {
                        for (int z2 = 0; z2 < currentState.getSize(); ++z2) {
                            if (x1 != x2 || y1 != y2 || z1 != z2) {
                                int value1 = currentState.getValue(x1, y1, z1);
                                int value2 = currentState.getValue(x2, y2, z2);

                                Cube neighbor = currentState.generateNeighbor(x1, y1, z1, x2, y2, z2);
                                int neighborObjectiveValue = neighbor.objectiveFunction();
                                neighborValues.push_back(make_tuple(neighbor, neighborObjectiveValue, value1, value2));
                                totalState++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void SteepestAscent::Algorithm() {
    auto start = high_resolution_clock::now();

    currentState = initialState;
    int currentObjectiveValue = currentState.objectiveFunction();

    bool foundBetter = true;

    while (foundBetter) {
        foundBetter = false;
        generateAllNeighbors();

        Cube bestNeighbor;
        int bestNeighborValue = currentObjectiveValue;
        int value1 = 0, value2 = 0;

        for (auto &neighborTuple : neighborValues) {
            Cube neighbor = std::get<0>(neighborTuple);
            int neighborObjectiveValue = std::get<1>(neighborTuple);
            int currentValue1 = std::get<2>(neighborTuple);
            int currentValue2 = std::get<3>(neighborTuple);

            if (neighborObjectiveValue > bestNeighborValue) {
                bestNeighbor = neighbor;
                bestNeighborValue = neighborObjectiveValue;
                value1 = currentValue1;
                value2 = currentValue2;
                foundBetter = true;
            }
        }

        if (foundBetter) {
            currentState = bestNeighbor;
            currentObjectiveValue = bestNeighborValue;
            addNextStep(currentState, value1, value2);
        }
    }

    finalState = currentState;
    if (finalState.objectiveFunction() == 0) {
        found = true;
    }

    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<duration<double>>(end - start).count();
}

