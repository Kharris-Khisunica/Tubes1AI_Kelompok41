#ifndef POSITION_H
#define POSITION_H

class Position {
private:
    int x, y, z;

public:
    Position();
    Position(int x, int y, int z);
    Position(const Position&);

    // Getter
    int getX();
    int getY();
    int getZ();

    // Setter
    void setX(int x);
    void setY(int y);
    void setZ(int z);

    bool isEmpty();
    bool operator==(const Position& other) const;

    void print();

};


#endif