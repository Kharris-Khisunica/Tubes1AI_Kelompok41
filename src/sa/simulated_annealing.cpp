#include <iostream>
#include <cmath>
#include "utils/Cube.cpp"
using namespace std;


class sa {

private:
    const double init_temp = 100;
    const double cutoff = 0.5;
    const double rate = 1 - 0.0001;
    const double minTemp = 0.001;
    const int maxIter = 1000;

    vector<Cube> cubeSeq; //Simpan sequence of Cube, untuk visualisasi
    Cube bestCube; //Cube terbaik

public:
    double nextTemp(double currtemp){
        return currtemp*rate;
    }

    bool isAccepted(const Cube& nowCube,const Cube& neighborCube, double currTemp){

        double stateValueCurr = getValue(nowCube);
        double stateValueNeig = getValue(neighborCube);
        // TENTUIN, DELTA E nya mau gimana
        double deltaE = stateValueNeig - stateValueCurr;

        if(deltaE > 0){
            return true;
        }
        else{
            return exp(-deltaE/currTemp) > cutoff;
        }
    }

    void simulatedAnnealing(){
        
        // Inisiasi
        int currIter = 0;
        double currTemp = init_temp;
        Cube currCube;
        currCube.randomizeCube();

        // While currIter < maxIter:
        while (currIter < maxIter && currTemp > minTemp)
        {
            // Generate One Neighbor secara random
            Cube neigCube = currCube.randomSwap();


            // Cek Acceptability
            if(isAccepted(currCube, neigCube, currTemp)){
                currCube = neigCube;
                cubeSeq.push_back(currCube);
                
                if(getValue(currCube) > getValue(bestCube)){
                    bestCube = currCube;
                }
            }

            //Atur currIter dan currTemp
            currIter++;
            currTemp = nextTemp(currTemp);


        }


    };

    vector<Cube> getCubeSeq() const{
        return cubeSeq;
    }
    
    Cube getBestCube() const{
        return bestCube;
    }
};