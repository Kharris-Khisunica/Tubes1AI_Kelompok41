#include <iostream>
#include "utils/Foo.cpp" 
#include "utils/Bar.cpp"
#include "utils/Cube.cpp"
#include "sa/simulated_annealing.cpp"

int main() {
    Cube cube;
    cube.randomizeCube();
    cube.printCube();

    cube.randomSwap();
    cube.printCube();

    return 0;
}
