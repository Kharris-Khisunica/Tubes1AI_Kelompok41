#include "../header/Stochastic.h"

Stochastic::Stochastic(Cube init, int maxIter) 
    : LocalSearch(init), gen(rd()), maxIterations(maxIter) {}

std::tuple<Cube, int, int, int> Stochastic::selectRandomNeighbor() {
    std::uniform_int_distribution<> dis(0, neighborValues.size() - 1);
    int randomIndex = dis(gen);
    return neighborValues[randomIndex];
}

void Stochastic::Algorithm() {
    auto start = high_resolution_clock::now();

    currentState = initialState;
    int currentObjectiveValue = currentState.objectiveFunction();
    int iterations = 0;
    bool improved = true;

    while (improved && iterations < maxIterations) {
        improved = false;
        generateAllNeighbors();

        int k = 10; 
        for (int i = 0; i < k; i++) {
            auto neighborTuple = selectRandomNeighbor();
            Cube neighbor = get<0>(neighborTuple);
            int neighborObjectiveValue = get<1>(neighborTuple);
            int swappedValue1 = get<2>(neighborTuple);
            int swappedValue2 = get<3>(neighborTuple);

            if (neighborObjectiveValue > currentObjectiveValue) {
                currentState = neighbor;
                currentObjectiveValue = neighborObjectiveValue;
                improved = true;
                iterations++;

                addNextStep(currentState, swappedValue1, swappedValue2);
                break;
            }
        }

        if (currentObjectiveValue == 0) {
            found = true;
            break;
        }
    }

    finalState = currentState;

    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<duration<double>>(end - start).count();
}