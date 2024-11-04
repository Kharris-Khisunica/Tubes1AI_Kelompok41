
#include "../header/SimulatedAnnealing.h"

    SimulatedAnnealing::SimulatedAnnealing(Cube init, double init_temp, double cutoff, double coolingRate, double minTemp, int maxIter, int totalLocalOptCount)
    : LocalSearch(init), init_temp(init_temp), cutoff(cutoff), coolingRate(coolingRate), minTemp(minTemp), maxIter(maxIter), totalLocalOptCount(totalLocalOptCount) {}


    
    double accProbs(int deltaE,double currTemp){
        return exp(-deltaE/currTemp);
    }

    void SimulatedAnnealing::Algorithm(){
        auto start = high_resolution_clock::now();

        currentState = initialState;
        int currentObjValue = currentState.objectiveFunction();
        int currIter = 0;
        int localOptCount = 0;
        int currTemp = init_temp;

        
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
                addNextStep(currentState,1,1);
                localOptSeq.push_back(1.0);
                
                
            }
            else if (deltaE <=0 && accProbs(deltaE, currTemp) > cutoff){
                currentState = neighbor;
                currentObjValue = neighborObjValue;
                addNextStep(currentState,1,1);
                localOptSeq.push_back(accProbs(deltaE,currTemp));
                localOptCount++;

            }

            currIter++;
            currTemp = currTemp*coolingRate;
            
        }

        auto end = high_resolution_clock::now();
        timeTaken = duration_cast<duration<double>>(end - start).count();
        totalLocalOptCount = localOptCount;
    }

