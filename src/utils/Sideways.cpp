#include "../header/Sideways.h"

Sideways::Sideways(Cube init, int sidewaysLimit) 
    : LocalSearch(init), sidewaysMoveLimit(sidewaysLimit) {}


void Sideways::Algorithm() {
    auto start = high_resolution_clock::now();

    currentState = initialState;
    int currentObjectiveValue = currentState.objectiveFunction();
    int sidewaysMoves = 0;
    bool foundBetter = true;

    while (foundBetter) {
        foundBetter = false;
        generateAllNeighbors();

        for (const auto &neighborTuple : neighborValues) {
            Cube neighbor = get<0>(neighborTuple);
            int neighborObjectiveValue = get<1>(neighborTuple);
            int swappedValue1 = get<2>(neighborTuple);
            int swappedValue2 = get<3>(neighborTuple);

            if (neighborObjectiveValue > currentObjectiveValue) {
                currentState = neighbor;
                currentObjectiveValue = neighborObjectiveValue;
                foundBetter = true;
                sidewaysMoves = 0; 
                addNextStep(currentState, swappedValue1, swappedValue2);
                break;
            } else if (neighborObjectiveValue == currentObjectiveValue && sidewaysMoves < sidewaysMoveLimit) {
                currentState = neighbor;
                foundBetter = true;
                sidewaysMoves++;
                addNextStep(currentState, swappedValue1, swappedValue2);
                break;
            }
        }

        if (!foundBetter || sidewaysMoves >= sidewaysMoveLimit) {
            break;
        }
    }

    finalState = currentState;
    if (finalState.objectiveFunction() == 0) {
        found = true;
    }

    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<duration<double>>(end - start).count();
}
