#include "../header/Cube.h"

// Constructor
Cube::Cube() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                setValue(i, j, k, 0);
            }
        }
    }
}

// Copy constructor
Cube::Cube(const Cube &cube) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                setValue(i, j, k, cube.matrix[i][j][k]);
            }
        }
    }
}

// Fungsi Get Value Matrix
int Cube::getValue(int x, int y, int z) {
    if (x >= 0 && x < size && y >= 0 && y < size && z >= 0 && z < size) {
        return matrix[x][y][z];
    } else {
        cout << "Index out of bounds." << endl;
        return -1;
    }
}

// Fungsi Set Value Matrix
void Cube::setValue(int x, int y, int z, int value) {
    if (x >= 0 && x < size && y >= 0 && y < size && z >= 0 && z < size) {
        matrix[x][y][z] = value;
    } else {
        cout << "Index out of bounds." << endl;
    }
}

int Cube::getSize(){
    return size;
}

// Fungsi menghitung State Value
int Cube::objectiveFunction() {
    int totalDifference = 0;

    // Sumbu X
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int rowSum = 0;
            for (int k = 0; k < size; k++) {
                rowSum += this->getValue(i, j, k);
            }
            totalDifference += abs(rowSum - magicnumber);
        }
    }

    // Sumbu Y
    for (int j = 0; j < size; j++) {
        for (int k = 0; k < size; k++) {
            int colSum = 0;
            for (int i = 0; i < size; i++) {
                colSum += this->getValue(i, j, k);
            }
            totalDifference += abs(colSum - magicnumber);
        }
    }

    // Sumbu Z
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            int pillarSum = 0;
            for (int j = 0; j < size; j++) {
                pillarSum += this->getValue(i, j, k);
            }
            totalDifference += abs(pillarSum - magicnumber);
        }
    }

    // Semua diagonal sisi
    for (int i = 0; i < size; i++) {
        int mainDiagSum1 = 0;
        int mainDiagSum2 = 0;
        for (int j = 0; j < size; j++) {
            mainDiagSum1 += this->getValue(i, j, j);
            mainDiagSum2 += this->getValue(i, j, (size - 1) - j);
        }
        totalDifference += abs(mainDiagSum1 - magicnumber);
        totalDifference += abs(mainDiagSum2 - magicnumber);
    }

    // Semua diagonal ruang
    int spaceDiag1 = 0, spaceDiag2 = 0, spaceDiag3 = 0, spaceDiag4 = 0;
    for (int i = 0; i < size; i++) {
        spaceDiag1 += this->getValue(i, i, i);
        spaceDiag2 += this->getValue(i, i, (size - 1) - i);
        spaceDiag3 += this->getValue(i, (size - 1) - i, i);
        spaceDiag4 += this->getValue(i, (size - 1) - i, (size - 1) - i);
    }
    totalDifference += abs(spaceDiag1 - magicnumber);
    totalDifference += abs(spaceDiag2 - magicnumber);
    totalDifference += abs(spaceDiag3 - magicnumber);
    totalDifference += abs(spaceDiag4 - magicnumber);

    return 0 - totalDifference;
}

// Fungsi Random Cube Initial
Cube Cube::randomizeCube() {
    vector<int> numbers(size*size*size);
    for (int i = 0; i < size*size*size; i++) {
        numbers[i] = i + 1;
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(numbers.begin(), numbers.end(), g);

    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                setValue(i, j, k, numbers[index++]);
            }
        }
    }
    return *this;
}

// Fungsi Generate Neighbor
Cube Cube::generateNeighbor(int x1, int y1, int z1, int x2, int y2, int z2) {
    Cube neighbor(*this);
    int temp = neighbor.getValue(x1, y1, z1);
    neighbor.setValue(x1, y1, z1, neighbor.getValue(x2, y2, z2));
    neighbor.setValue(x2, y2, z2, temp);
    return neighbor;
}

// Fungsi Print Jaring-Jaring Kubus
void Cube::printCube() { 
    cout << "Sisi X Kubus:" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                cout << setw(4) << matrix[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;

    cout << "Sisi Y Kubus:" << endl;
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int k = 0; k < size; k++)
            {
                cout << setw(4) << matrix[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;

    cout << "Sisi Z Kubus:" << endl;
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << setw(4) << matrix[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}