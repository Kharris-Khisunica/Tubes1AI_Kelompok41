#include "../header/SimulatedAnnealing.h"

    SimulatedAnnealing::SimulatedAnnealing(Cube init, double init_temp, double cutoff, double coolingRate, double minTemp, int maxIter, int totalLocalOptCount)
    : LocalSearch(init), init_temp(init_temp), cutoff(cutoff), coolingRate(coolingRate), minTemp(minTemp), maxIter(maxIter), totalLocalOptCount(totalLocalOptCount) {}


    
    double SimulatedAnnealing::accProbs(int deltaE,double currTemp){
        return exp(-deltaE/currTemp);
    }

    void SimulatedAnnealing::Algorithm(){
        auto start = high_resolution_clock::now();

        currentState = initialState;
        int currentObjValue = currentState.objectiveFunction();
        int currIter = 0;
        int localOptCount = 0;
        double currTemp = init_temp;

        
        while(currIter < maxIter && currTemp > minTemp){
            tuple<Cube,int,int,int> neighborTuple = generateRandomNeighbor(currentState);
            
            Cube neighbor = get<0>(neighborTuple);
            int neighborObjValue = get<1>(neighborTuple);
            int swappedValue1 = get<2>(neighborTuple);
            int swappedValue2 = get<3>(neighborTuple);

            int deltaE = neighborObjValue - currentObjValue;

            if(deltaE > 0){
                currentState = neighbor;
                currentObjValue = neighborObjValue;
                addNextStepSA(currentState,swappedValue1,swappedValue2,1);
                
                
                
            }
            else if (deltaE <=0 && accProbs(deltaE, currTemp) > cutoff){
                currentState = neighbor;
                currentObjValue = neighborObjValue;
                addNextStepSA(currentState,swappedValue1,swappedValue2,accProbs(deltaE,currTemp));
                
            }

            currIter++;
            currTemp = currTemp*coolingRate;
            
        }

        auto end = high_resolution_clock::now();
        timeTaken = duration_cast<duration<double>>(end - start).count();
        totalLocalOptCount = localOptCount;
    }

    void SimulatedAnnealing::addNextStepSA(Cube nextState, int value1, int value2, double value3)
    {
        allStepSA.emplace_back(nextState, value1, value2,value3);
        totalStep++;
    }

    vector<tuple<Cube, int, int, double>> SimulatedAnnealing::getAllStepsSA() {
        return allStepSA;
    }