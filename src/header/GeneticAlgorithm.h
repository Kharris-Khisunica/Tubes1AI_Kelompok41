#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "LocalSearch.h"

class GeneticAlgorithm : public LocalSearch {
private:
    vector<tuple<Cube, int>> initialPopulation;
    int populationSize;
    int maxIteration;
    double mutationProbability;

public:
    GeneticAlgorithm(Cube init, int populationSize, int maxIteration);

    tuple<Cube, int> chooseParent(vector<tuple<Cube, int>> &currentPopulation);

    void Algorithm();

    vector<tuple<Cube, int>> reproduce(tuple<Cube, int> &parent1, tuple<Cube, int> &parent2);

    tuple<Cube, int> chooseBestIndividual(vector<tuple<Cube, int>> population);
};

#endif