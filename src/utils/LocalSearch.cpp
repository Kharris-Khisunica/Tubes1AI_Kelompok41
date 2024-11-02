#include "../header/LocalSearch.h"

LocalSearch::LocalSearch(Cube init) {
    initialState = init;
    currentState = init;
    finalState = init;
    timeTaken = 0;
    totalState = 0;
    totalStep = 0;
    found = false;
}

Cube LocalSearch::getInitialState() {
    return initialState;
}

Cube LocalSearch::getCurrentState() {
    return currentState;
}

Cube LocalSearch::getFinalState() {
    return finalState;
}

double LocalSearch::getTimeTaken() {
    return timeTaken;
}

int LocalSearch::getTotalState() {
    return totalState;
}

bool LocalSearch::isFound() {
    return found;
}

vector<tuple<Cube, int, int>> LocalSearch::getAllSteps() {
    return allStep;
}

int LocalSearch::getTotalStep() {
    return totalStep;
}

void LocalSearch::addNextStep(Cube nextState, int value1, int value2) {
    allStep.emplace_back(nextState, value1, value2);
    totalStep++;
}