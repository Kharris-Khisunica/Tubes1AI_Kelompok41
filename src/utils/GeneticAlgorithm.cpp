#include "../header/GeneticAlgorithm.h"
#include "../header/Position.h"
#include <cstdlib>

GeneticAlgorithm::GeneticAlgorithm(Cube init, int populationSize, int maxIteration) : LocalSearch(init)
{
    this->populationSize = populationSize;
    this->maxIteration = maxIteration;
    this->mutationProbability = 0.001;

    for (int i = 0; i < populationSize; ++i)
    {
        Cube newIndividual = init.randomizeCube();
        int objectiveValue = newIndividual.objectiveFunction();
        initialPopulation.push_back(make_tuple(newIndividual, objectiveValue));
    }
}

tuple<Cube, int> GeneticAlgorithm::chooseParent(vector<tuple<Cube, int>> &currentPopulation)
{
    int sumObjectiveValue = 0;
    for (int i = 0; i < populationSize; ++i)
    {
        sumObjectiveValue += get<1>(currentPopulation[i]);
    }

    vector<double> wheel(populationSize);
    wheel[0] = get<1>(currentPopulation[0]) / (float) sumObjectiveValue;

    for (int i = 1; i < populationSize; ++i)
    {
        wheel[i] = (get<1>(currentPopulation[i]) / (float) sumObjectiveValue) + wheel[i-1];
    }

    double randomProbability = generateRandomRealNumber(0.0, 1.0);

    tuple<Cube, int> res;
    for (int i = 0; i < populationSize; ++i)
    {
        if (wheel[i] > randomProbability)
        {
            res = currentPopulation[i]; 
            break;
        }
    }

    return res;
}

void GeneticAlgorithm::Algorithm()
{
    auto start = high_resolution_clock::now();

    vector<tuple<Cube, int>> currentPopulation = initialPopulation;
    int currentIteration = 1;

    while (!found && currentIteration <= maxIteration)
    {
        // cout << "Iterasi ke-" << currentIteration << ": " << endl;
        vector<tuple<Cube, int>> nextPopulation;

        while (!found && nextPopulation.size() < populationSize)
        {
            tuple<Cube, int> parent1 = chooseParent(currentPopulation);
            tuple<Cube, int> parent2 = chooseParent(currentPopulation);

            vector<tuple<Cube, int>> children = reproduce(parent1, parent2);
            
            for (int i = 0; i < children.size(); ++i)
            {
                double randomProbability = generateRandomRealNumber(0.0, 1.0);
                if (randomProbability < mutationProbability)
                {
                    Cube childrenCube = get<0>(children[i]);
                    tuple<Cube, int, int, int> mutatedChildren = generateRandomNeighbor(childrenCube);
                    children[i] = make_tuple(get<0>(mutatedChildren), get<1>(mutatedChildren));
                }
            }

            if (get<0>(children[0]).objectiveFunction() == 0)
            {
                found = true;
                finalState = get<0>(children[0]);
            }
            else if (get<0>(children[1]).objectiveFunction() == 0)
            {
                found = true;
                finalState = get<0>(children[1]);
            }

            nextPopulation.insert(nextPopulation.end(), children.begin(), children.end());
        }

        currentPopulation = nextPopulation;
        currentIteration++;
    }

    totalState = currentIteration * populationSize;
    totalStep = currentIteration;

    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<duration<double>>(end - start).count();

    if (found) return;

    tuple<Cube, int> bestState = chooseBestIndividual(currentPopulation);
    finalState = get<0>(bestState);
}

vector<tuple<Cube, int>> GeneticAlgorithm::reproduce(tuple<Cube, int> &parent1, tuple<Cube, int> &parent2)
{
    Cube parentCube1 = get<0>(parent1);
    Cube parentCube2 = get<0>(parent2);

    int n = initialState.getSize();
    vector<Position> position1(pow(n, 3));
    vector<Position> position2(pow(n, 3));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                position1[parentCube1.getValue(i, j, k) - 1] = Position(i, j, k);
                position2[parentCube2.getValue(i, j, k) - 1] = Position(i, j, k);
            }
        }
    }

    vector<Position> positionChild1(pow(n, 3));
    vector<Position> positionChild2(pow(n, 3));

    int halfPosSize = pow(n, 3) / 2;

    for (int i = 0; i < halfPosSize; ++i)
    {
        positionChild1[i] = position1[i];
        positionChild2[i] = position2[i];
    }


    vector<int> conflictingValues1;
    vector<int> conflictingValues2;

    for (int i = halfPosSize; i < pow(n, 3); ++i)
    {
        bool isPositionConflict1 = false;
        bool isPositionConflict2 = false;
        int conflictIdx1 = -1;
        int conflictIdx2 = -1;

        for (int j = 0; j < halfPosSize; ++j)
        {
            // Child 1
            if (position1[j] == position2[i])
            {
                isPositionConflict1 = true;
                conflictIdx1 = j;
            }

            // Child 2
            if (position2[j] == position1[i])
            {
                isPositionConflict2 = true;
                conflictIdx2 = j;
            }
        }

        // Child 1
        if (!isPositionConflict1)
        {
            positionChild1[i] = position2[i];
        }
        else
        {
            double randomProbability = generateRandomRealNumber(0.0, 1.0);
            if (randomProbability < 0.5)
            {
                conflictingValues1.push_back(i+1);
            }
            else
            {
                positionChild1[conflictIdx1] = Position();
                positionChild1[i] = position2[i];
                conflictingValues1.push_back(conflictIdx1 + 1);
            }
        }

        // Child 2
        if (!isPositionConflict2)
        {
            positionChild2[i] = position1[i];
        }
        else
        {
            double randomProbability = generateRandomRealNumber(0.0, 1.0);
            if (randomProbability < 0.5)
            {
                conflictingValues2.push_back(i+1);
            }
            else
            {
                positionChild2[conflictIdx2] = Position();
                positionChild2[i] = position1[i];
                conflictingValues2.push_back(conflictIdx2 + 1);
            }
        }
    }

    Cube childCube1;
    Cube childCube2;

    for (int i = 0; i < pow(n, 3); ++i)
    {
        Position pos1 = positionChild1[i];
        Position pos2 = positionChild2[i];

        if (!pos1.isEmpty())
        {
            childCube1.setValue(pos1.getX(), pos1.getY(), pos1.getZ(), i+1);
        }
        if (!pos2.isEmpty())
        {
            childCube2.setValue(pos2.getX(), pos2.getY(), pos2.getZ(), i+1);
        }
    }

    vector<Position> emptyPositions1;
    vector<Position> emptyPositions2;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                if (childCube1.getValue(i, j, k) == 0)
                {
                    emptyPositions1.push_back(Position(i, j, k));
                }

                if (childCube2.getValue(i, j, k) == 0)
                {
                    emptyPositions2.push_back(Position(i, j, k));
                }
            }
        }
    }

    for (int i = 0; i < conflictingValues1.size(); ++i)
    {
        Position pos1 = emptyPositions1[i];
        Position pos2 = emptyPositions2[i];

        childCube1.setValue(pos1.getX(), pos1.getY(), pos1.getZ(), conflictingValues1[i]);
        childCube2.setValue(pos2.getX(), pos2.getY(), pos2.getZ(), conflictingValues2[i]);
    }

    tuple<Cube, int> tuple1 = make_tuple(childCube1, childCube1.objectiveFunction());
    tuple<Cube, int> tuple2 = make_tuple(childCube2, childCube2.objectiveFunction());

    return {tuple1, tuple2};
}

tuple<Cube, int> GeneticAlgorithm::chooseBestIndividual(vector<tuple<Cube, int>> population)
{
    tuple<Cube, int> bestIndividual;
    int bestObjectiveValue = -999999;
    int bestIdx = -1;

    for (int i = 0; i < population.size(); i++)
    {
        if (get<1>(population[i]) > bestObjectiveValue)
        {
            bestIndividual = population[i];
        }
    }

    return bestIndividual;
}