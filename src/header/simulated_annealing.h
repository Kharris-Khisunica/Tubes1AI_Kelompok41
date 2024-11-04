
// #ifndef SIMULATED_ANNEALING_H
// #define SIMULATED_ANNEALING_H

// #include <iostream>
// #include <cmath>
// #include <vector>
// #include <cstdlib>
// #include <utility>
// #include "Cube.h"
// using namespace std;

// class SA{

// private:
//     const double init_temp = 100;
//     const double cutoff = 0.5; //Batas minimum state value kalau lebih jelek
//     const double rate = 1 - 0.0001;
//     const double minTemp = 1e-10;
//     const int maxIter = 1000;
//     int set[3];

//     vector<Cube> cubeSeq; //Simpan sequence of Cube, untuk visualisasi
//     vector<int> ObjFuncSeq; //Sequence of Objective Function untuk visualisasi
//     vector<double> localOptSeq; //Sequence of Local Optima (Yg masuk ke e^(-deltaE/T))
//     Cube bestCube; //Cube terbaik

// public:

//     SA() : bestCube(){}

//     //Next Temperatur di iterasi berikutnya
//     double nextTemp(double init_temp);

//     //Buat Random Neighbor/Lokasi nya saja
//     pair<int*, int*> generateNeighborLoc();

//     //Cek apakah Cube neighbor memiliki statevalue yang diterima
//     bool isAccepted(Cube nowCube,Cube neighborCube, double nowTemp);

//     //Dapatkan Cube Sequence
//     vector<Cube> getCubeSeq() const;
    
//     //Dapatkan Cube terakhir
//     Cube getBestCube() const;

//     //Dapatkan Objective Function Sequence
//     vector<int> getObjFuncSeq() const;

//     //Dapatkan Local Optimal Seq
//     vector<double> SA::getLocalOptSeq() const;

//     //Simulated Annealing
//     void simulatedAnnealing();

    

    
// };

// #endif
