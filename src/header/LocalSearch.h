#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "Cube.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class LocalSearch {
protected:
    Cube initialState;
    Cube currentState;
    Cube finalState;
    double timeTaken;
    int totalState;

    bool found;

    // List Semua Step
    vector<tuple<Cube, int, int>> allStep;
    int totalStep;

public:
    // Constructor
    LocalSearch(Cube init);

    // Fungsi Primitif
    Cube getInitialState();
    Cube getCurrentState();
    Cube getFinalState();
    double getTimeTaken();
    int getTotalState();
    bool isFound();
    vector<tuple<Cube, int, int>> getAllSteps();
    int getTotalStep();

    // Fungsi Add Decision
    void addNextStep(Cube nextState, int value1, int value2);

    // Fungsi Generate Neighbor
    tuple<Cube, int, int, int> generateRandomNeighbor(Cube state);
    vector<tuple<Cube, int, int, int>> generateAllNeighbors();

    // Fungsi Generate Random Value
    int generateRandomInteger(int minValue, int maxValue);
    double generateRandomRealNumber(double minValue, double maxValue);
};

#endif
