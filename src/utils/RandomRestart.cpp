#include "../header/RandomRestart.h"
#include <random>
#include <climits>

RandomRestart::RandomRestart(Cube init, int maxRestarts, int maxIterationsPerRestart) 
    : LocalSearch(init), maxRestarts(maxRestarts), maxIterationsPerRestart(maxIterationsPerRestart) {
    bestObjectiveValue = INT_MIN;
}

void RandomRestart::generateAllNeighbors() {
    neighborValues.clear();

    for (int x1 = 0; x1 < initialState.getSize(); ++x1) {
        for (int y1 = 0; y1 < initialState.getSize(); ++y1) {
            for (int z1 = 0; z1 < initialState.getSize(); ++z1) {
                for (int x2 = 0; x2 < initialState.getSize(); ++x2) {
                    for (int y2 = 0; y2 < initialState.getSize(); ++y2) {
                        for (int z2 = 0; z2 < initialState.getSize(); ++z2) {
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

void RandomRestart::hillClimbingIteration(int maxIterations) {
    int iterations = 0;
    int currentObjectiveValue = currentState.objectiveFunction();
    bool foundBetter = true;

    while (foundBetter && iterations < maxIterations) {
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

                addNextStep(currentState, swappedValue1, swappedValue2);
                iterations++;
                break; 
            }
        }
    }

    iterationsPerRestart.push_back(iterations);

    if (currentObjectiveValue > bestObjectiveValue) {
        bestObjectiveValue = currentObjectiveValue;
        bestState = currentState;
    }
}

Cube generateRandomState(Cube& initialCube) {
    Cube randomCube = initialCube;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    int size = initialCube.getSize();
    // MODIF DI SINI
    int numSwaps = 100; 
    
    for (int i = 0; i < numSwaps; i++) {
        std::uniform_int_distribution<> dis(0, size - 1);
        int x1 = dis(gen), y1 = dis(gen), z1 = dis(gen);
        int x2 = dis(gen), y2 = dis(gen), z2 = dis(gen);
        
        if (x1 != x2 || y1 != y2 || z1 != z2) {
            randomCube = randomCube.generateNeighbor(x1, y1, z1, x2, y2, z2);
        }
    }
    
    return randomCube;
}

void RandomRestart::Algorithm() {
    auto start = high_resolution_clock::now();

    for (int restart = 0; restart < maxRestarts; restart++) {
        currentState = generateRandomState(initialState);
        
        hillClimbingIteration(maxIterationsPerRestart);

        if (bestObjectiveValue == 0) {
            found = true;
            break;
        }
    }

    finalState = bestState;

    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<duration<double>>(end - start).count();
}