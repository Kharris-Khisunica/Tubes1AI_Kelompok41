
#include "./header/simulated_annealing.h"


    double SA::nextTemp(double currtemp){
        return currtemp*rate;
    }

    bool SA::isAccepted(Cube nowCube,Cube neighborCube, double currTemp){

        double stateValueCurr = nowCube.objectiveFunction();
        double stateValueNeig = neighborCube.objectiveFunction();
        // TENTUIN, DELTA E nya mau gimana
        double deltaE = stateValueNeig - stateValueCurr;

        if(deltaE > 0){
            return true;
        }
        else{
            return exp(-deltaE/currTemp) > cutoff;
        }
    }

    pair<int*, int*> SA::generateNeighborLoc(){
        static int set1[3], set2[3];
        
        for (int i=0; i<3; i++){
            set1[i] = rand()%5;
        }
        do{
            for (int i=0; i<3; i++){
            set2[i] = rand()%5;
            }
        }while(equal(begin(set1), end(set1), begin(set2)));

        return make_pair(set1,set2);
    }

    void SA::simulatedAnnealing(){
        
        // Inisiasi
        int currIter = 0;
        double currTemp = init_temp;
        Cube currCube;
        currCube.randomizeCube();
        bestCube = currCube;

        // While currIter < maxIter:
        while (currIter < maxIter && currTemp > minTemp)
        {
            // Generate One Neighbor secara random
            auto loc = generateNeighborLoc();
            int* loc1 = loc.first;
            int* loc2 = loc.second;
            Cube neigCube = currCube.generateNeighbor(loc1[0],loc1[1],loc1[2],loc2[0],loc2[1],loc2[2]);


            // Cek Acceptability
            if(isAccepted(currCube, neigCube, currTemp)){
                currCube = neigCube;
                cubeSeq.push_back(currCube);
                
                if(currCube.objectiveFunction() > bestCube.objectiveFunction()){
                    bestCube = currCube;
                }
            }

            //Atur currIter dan currTemp
            currIter++;
            currTemp = nextTemp(currTemp);


        }


    };

    vector<Cube> SA::getCubeSeq() const{
        return cubeSeq;
    }
    
    Cube SA::getBestCube() const{
        return bestCube;
    }
