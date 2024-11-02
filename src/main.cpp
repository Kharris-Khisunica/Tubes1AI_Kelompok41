#include <iostream>
#include "header/Cube.h"
#include "header/SteepestAscent.h"

int main() {
    Cube initialCube;
    initialCube.randomizeCube();
    initialCube.printCube();
    cout << "Objective Function Value: " << initialCube.objectiveFunction() << endl;

    SteepestAscent steepest(initialCube);

    steepest.Algorithm();

    cout << "All Steps:" << endl;
    vector<tuple<Cube, int, int>> steps = steepest.getAllSteps();
    int i = 1;
    for (auto &step : steps) {
        Cube cube = std::get<0>(step);
        cout << "Step " << i + 1 << ":" << endl;
        cube.printCube();
        cout << "Objective Function Value: " << cube.objectiveFunction() << endl;
        i++;
    }

    cout << "Objective Function Value of Final State: " << steepest.getFinalState().objectiveFunction() << endl;

    cout << "Time Taken (seconds): " << steepest.getTimeTaken() << endl;
    cout << "Total States Visited: " << steepest.getTotalState() << endl;
    cout << "Total Step: " << steepest.getTotalStep() << endl;

    cout << "Optimal Solution Found: " << (steepest.isFound() ? "Yes" : "No") << endl;

    return 0;
}