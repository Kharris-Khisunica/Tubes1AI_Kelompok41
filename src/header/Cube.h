#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Cube {
private:
    static const int size = 5;
    int matrix[size][size][size];
    static const int magicnumber = size * (size*size*size + 1)/2;

public:
    // Constructor
    Cube();

    // Copy Constructor
    Cube(const Cube &cube);

    // Fungsi Primitif
    int getValue(int x, int y, int z);
    void setValue(int x, int y, int z, int value);
    int getSize();

    // Fungsi menghitung State Value
    int objectiveFunction();

    // Fungsi Random Cube Initial
    Cube randomizeCube();

    // Fungsi GenerateNeighbor
    Cube generateNeighbor(int x1, int y1, int z1, int x2, int y2, int z2);

    // Fungsi Print Jaring-Jaring Kubus
    void printCube(ofstream& out);

    // Fungsi Load Cube dari File
    bool loadFromFile(const string& filename);
};

#endif
