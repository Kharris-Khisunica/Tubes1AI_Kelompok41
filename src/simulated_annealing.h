#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include "util.h"

double nowTemp(double init_temp);

bool isAccepted(double nowCube,double neighborCube, double nowTemp);




#endif