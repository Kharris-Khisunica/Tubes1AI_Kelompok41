#include "../header/Sideways.h"

// Constructor
Sideways::Sideways(Cube init, int sidewaysLimit) : LocalSearch(init), sidewaysMoveLimit(sidewaysLimit)  {}


void Sideways::Algorithm() {
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

            if (neighborObjectiveValue >= bestNeighborValue) {
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

