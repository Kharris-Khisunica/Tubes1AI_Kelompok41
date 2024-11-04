
#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <utility>
#include "LocalSearch.h"
using namespace std;

class SimulatedAnnealing : public LocalSearch{

private:
    const double init_temp = 100;
    const double cutoff = 0.5; //Batas minimum state value kalau lebih jelek
    const double coolingRate = 1 - 0.0001;
    const double minTemp = 1e-10;
    const int maxIter = 1000;
    int totalLocalOptCount;

    vector<tuple<Cube,int,int,int>> neighbourValue;
    vector<double> localOptSeq;
    Cube bestCube; //Cube terbaik

public:

    SimulatedAnnealing(Cube init, double init_temp, double cutoff, double coolingRate, double minTemp, int maxIter, int totalLocalOptCount);

    
    
    // Hitung Acceptability Probability
    double accProbs(int deltaE,double currTemp);

    
    void Algorithm();

    vector<double> getLocalOptSeq() const {return localOptSeq;}
    int getTotalLocalOptCount() const {return totalLocalOptCount;}

    

    
};

#endif
