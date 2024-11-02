#include <iostream>
#include <cmath>
#include "util.h"
using namespace std;

const double e = exp(1.0);
const double cutoff = 0.5;
const double rate = 1 - 0.0001;

double nowTemp(double init_temp){

    double nowTemp;

    nowTemp = init_temp*rate;

    return nowTemp;

};

bool isAccepted(double nowCube,double neighborCube, double nowTemp){

    double state_value_now = statevalue(nowCube);
    double state_value_neighbor = statevalue(neighborCube);
    // TENTUIN, DELTA E nya mau gimana
    double deltaE = state_value_neighbor - state_value_now;

    if(deltaE > 0){
        return true;
    }
    else{
        if(exp(-1*deltaE/nowTemp) > cutoff){
            return true;
        }
        else{
            return false;
        }
    }
};



