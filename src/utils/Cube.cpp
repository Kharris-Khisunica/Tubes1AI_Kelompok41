#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Cube {
private:
    int matrix[6][5][5];

public:
    Cube() {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 5; ++j) {
                for (int k = 0; k < 5; ++k) {
                    setValue(i, j, k, 0);
                }
            }
        }
    }

    // Fungsi Random Cube Initial
    void randomizeCube() {
        vector<int> numbers(150);
        for (int i = 0; i < 150; ++i) {
            numbers[i] = i + 1;
        }

        random_device rd;
        mt19937 g(rd());
        shuffle(numbers.begin(), numbers.end(), g);

        int index = 0;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 5; ++j) {
                for (int k = 0; k < 5; ++k) {
                    setValue(i, j, k, numbers[index++]);
                }
            }
        }
    }

    // Fungsi Random Swap 2 Value
    void randomSwap() {
        random_device rd;
        mt19937 g(rd());

        uniform_int_distribution<int> faceDist(0, 5);
        uniform_int_distribution<int> rowColDist(0, 4);

        int face1 = faceDist(g);
        int row1 = rowColDist(g);
        int col1 = rowColDist(g);

        int face2, row2, col2;
        do {
            face2 = faceDist(g);
            row2 = rowColDist(g);
            col2 = rowColDist(g);
        } while (face1 == face2 && row1 == row2 && col1 == col2);

        int temp = getValue(face1, row1, col1);
        setValue(face1, row1, col1, getValue(face2, row2, col2));
        setValue(face2, row2, col2, temp);

        cout << "Swapped values at (" << face1+1 << ", " << row1+1 << ", " << col1+1 << ") and ("
             << face2+1 << ", " << row2+1 << ", " << col2+1 << ")" << endl;
    }

    // Fungsi Set Value Matrix
    void setValue(int face, int row, int col, int value) {
        if (face >= 0 && face < 6 && row >= 0 && row < 5 && col >= 0 && col < 5) {
            matrix[face][row][col] = value;
        } else {
            cout << "Index out of bounds." << endl;
        }
    }

    // Fungsi Get Value Matrix
    int getValue(int face, int row, int col) const {
        if (face >= 0 && face < 6 && row >= 0 && row < 5 && col >= 0 && col < 5) {
            return matrix[face][row][col];
        } else {
            cout << "Index out of bounds." << endl;
            return -1;
        }
    }

    // Fungsi Print 1 Sisi Kubus
    void printFace(int face) const {
        cout << setw(52);
        for (int col = 0; col < 5; ++col) {
            cout << " _______";
        }

        cout << endl;
        for (int row = 0; row < 5; ++row) {
            cout << setw(45);
            for (int col = 0; col < 5; ++col) {
                cout << "|" << setw(8); 
            }
            cout << "|" << endl;

            cout << setw(46);
            for (int col = 0; col < 5; ++col) {
                cout << "| " << setw(3) << getValue(face, row, col) << setw(3) << " "; 
            }
            cout << "|" << endl;

            cout << setw(52);
            for (int col = 0; col < 5; ++col) {
                cout << "|_______";
            }
            cout << "|" << endl;
        }
        cout << endl; 
    }

    // Fungsi Print Jaring-Jaring Kubus
    void printCube() const {
        printFace(2);
        printFace(1);

        for (int col = 0; col < 5; ++col) {
            cout << " _______";
        }
        cout << "    ";


        for (int col = 0; col < 5; ++col) {
            cout << " _______";
        }
        cout << "    ";


        for (int col = 0; col < 5; ++col) {
            cout << " _______";
        }
        cout << endl;

        for (int row = 0; row < 5; ++row) {
            for (int face = 0; face < 3; ++face) {
                for (int col = 0; col < 5; ++col) {
                    cout << "|       ";
                }
                cout << "|   ";
            }
            cout << endl;

            for (int face : {4, 0, 5}) {
                for (int col = 0; col < 5; ++col) {
                    cout << "| " << setw(3) << getValue(face, row, col) << setw(3) << " ";
                }
                cout << "|   ";
            }
            cout << endl;

    
            for (int face = 0; face < 3; ++face) {
                for (int col = 0; col < 5; ++col) {
                    cout << "|_______";
                }
                cout << "|   ";
            }
            cout << endl;
        }
        cout << endl;

        printFace(3);
        cout << endl;
    }
};
