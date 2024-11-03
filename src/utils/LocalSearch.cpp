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

tuple<Cube, int, int, int> LocalSearch::generateRandomNeighbor(Cube state)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, state.getSize() - 1);

    vector<int> position1(3);
    vector<int> position2(3);
    bool isMoveValid = false;

    while (!isMoveValid) {
        for (int i = 0; i < 3; ++i)  {
            position1[i] = dist(gen);
            position2[i] = dist(gen);
        }

        if (position1 != position2) {
            isMoveValid = true;
        }
    }

    Cube neighbor = state.generateNeighbor(position1[0], position1[1], position1[2], position2[0], position2[1], position2[2]);
    int value1 = state.getValue(position1[0], position1[1], position1[2]);
    int value2 = state.getValue(position2[0], position2[1], position2[2]);

    return make_tuple(neighbor, neighbor.objectiveFunction(), value1, value2);
}

std::vector<std::tuple<Cube, int, int, int>> LocalSearch::generateAllNeighbors() {
    vector<tuple<Cube, int, int, int>> neighborValues;

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

    return neighborValues;
}

int LocalSearch::generateRandomInteger(int minValue, int maxValue)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(minValue, maxValue);

    return dist(gen);
}

double LocalSearch::generateRandomRealNumber(double minValue, double maxValue)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);

    return dist(gen);
}