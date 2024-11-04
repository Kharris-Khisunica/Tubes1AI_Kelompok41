#include <iostream>
#include <fstream>
#include <sstream>
#include "header/Cube.h"
#include "header/SteepestAscent.h"
#include "header/GeneticAlgorithm.h"
#include "header/RandomRestart.h"
#include "header/Stochastic.h"
#include "header/SimulatedAnnealing.h"
#include "header/Sideways.h"
// #include "header/Sideways.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Usage: " << argv[0] << " <algorithm_name> [cube_file]" << endl;
        return 1;
    }

    string algorithm = argv[1];
    Cube initialCube;

    if (argc == 3) {
        string cubeFile = argv[2];
        if (!initialCube.loadFromFile(cubeFile)) {
            return 1;
        }
    } else {
        initialCube.randomizeCube();  // Randomize if no file provided
    }

    ofstream outputFile("output.txt", ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    if (algorithm == "SteepestAscent") {
        SteepestAscent steepest(initialCube);
        steepest.Algorithm();

        vector<tuple<Cube, int, int>> steps = steepest.getAllSteps();
        int totalSteps = steps.size();
        double timeTaken = steepest.getTimeTaken();
        int totalCubesGenerated = steepest.getTotalState();
        bool isFound = steepest.isFound();

        outputFile << initialCube.getSize() << " " << totalSteps << " " << totalCubesGenerated << " " 
                   << timeTaken << " " << (isFound ? "1" : "0") << endl;

        int initialObjValue = initialCube.objectiveFunction();
        outputFile << "0 " << initialObjValue << " 0 0" << endl;
        initialCube.printCube(outputFile);

        int stepNumber = 1;
        for (const auto& step : steps) {
            Cube cube = get<0>(step);
            int objValue = cube.objectiveFunction();
            int value1 = get<1>(step);
            int value2 = get<2>(step);
        

            outputFile << stepNumber << " " << objValue << " " <<  value1 << " " <<  value2 << endl;

            cube.printCube(outputFile);

            stepNumber++;
        }
    }
    else if (algorithm == "GeneticAlgorithm") {
        int populationSize;
        cout << "Masukkan ukuran populasi: ";
        cin >> populationSize;

        int maxIteration;
        cout << "Masukkan jumlah maksimal iterasi: ";
        cin >> maxIteration;

        GeneticAlgorithm genetic(initialCube, populationSize, maxIteration);
        genetic.Algorithm();

        vector<tuple<Cube, int, int>> steps = genetic.getAllSteps();
        int totalSteps = steps.size();
        double timeTaken = genetic.getTimeTaken();
        int totalCubesGenerated = genetic.getTotalState();
        bool isFound = genetic.isFound();

        outputFile << initialCube.getSize() << " " << totalSteps << " " << totalCubesGenerated << " " 
                   << timeTaken << " " << (isFound ? "1" : "0") << endl;

        int initialObjValue = initialCube.objectiveFunction();
        outputFile << "0 " << initialObjValue << " 0 0" << endl;
        initialCube.printCube(outputFile);

        int stepNumber = 1;
        for (const auto& step : steps)
        {
            Cube cube = get<0>(step);
            int objValue = cube.objectiveFunction();
            int value1 = get<1>(step);
            int value2 = get<2>(step);

            outputFile << stepNumber << " " << objValue << " " <<  value1 << " " <<  value2 << endl;

            cube.printCube(outputFile);

            stepNumber++;
        }
    }
    else if (algorithm == "SimulatedAnnealing"){
        const double init_temp = 100;
        const double cutoff = 0.5; 
        const double coolingRate = 1 - 0.0001;
        const double minTemp = 1e-10;
        const int maxIter = 1000;
        int totalLocalOptCount;

        SimulatedAnnealing sa(initialCube, init_temp, cutoff, coolingRate, minTemp, maxIter, totalLocalOptCount);
        sa.Algorithm();

        vector<tuple<Cube, int, int, double>> steps = sa.getAllStepsSA();
        int totalSteps = steps.size();
        double timeTaken = sa.getTimeTaken();
        int totalCubesGenerated = sa.getTotalState();
        bool isFound = sa.isFound();

        outputFile << initialCube.getSize() << " " << totalSteps << " " << totalCubesGenerated << " " 
                   << timeTaken << " " << (isFound ? "1" : "0") << endl;

        int initialObjValue = initialCube.objectiveFunction();
        outputFile << "0 " << initialObjValue << " 0 0 0" << endl;
        initialCube.printCube(outputFile);

        int stepNumber = 1;

        for (const auto& step : steps) {
            Cube cube = get<0>(step);
            int objValue = cube.objectiveFunction();
            int value1 = get<1>(step);
            int value2 = get<2>(step);
            int value3 = get<3>(step);

            outputFile << stepNumber << " " << objValue << " " <<  value1 << " " <<  value2 << " " << value3 << endl;

            cube.printCube(outputFile);

            stepNumber++;
        }
    }
    else if (algorithm == "SidewaysMove") {
        Sideways steepest(initialCube, 100);
        steepest.Algorithm();
        vector<tuple<Cube, int, int>> steps = steepest.getAllSteps();
        int totalSteps = steps.size();
        double timeTaken = steepest.getTimeTaken();
        int totalCubesGenerated = steepest.getTotalState();
        bool isFound = steepest.isFound();
        outputFile << initialCube.getSize() << " " << totalSteps << " " << totalCubesGenerated << " " 
                   << timeTaken << " " << (isFound ? "1" : "0") << endl;
        int initialObjValue = initialCube.objectiveFunction();
        outputFile << "0 " << initialObjValue << " 0 0" << endl;
        initialCube.printCube(outputFile);
        int stepNumber = 1;
        for (const auto& step : steps) {
            Cube cube = get<0>(step);
            int objValue = cube.objectiveFunction();
            int value1 = get<1>(step);
            int value2 = get<2>(step);
            outputFile << stepNumber << " " << objValue << " " <<  value1 << " " <<  value2 << endl;
            cube.printCube(outputFile);
            stepNumber++;
        }
    }
    else if (algorithm == "RandomRestart") {
        RandomRestart steepest(initialCube,2);
        steepest.Algorithm();
    }
    else {
        cerr << "Unknown algorithm: " << algorithm << endl;
        outputFile.close();
        return 1;
    }

    outputFile.close();
    return 0;
}

