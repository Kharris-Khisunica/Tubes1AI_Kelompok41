#include "../header/Position.h"
#include <iostream>

Position::Position()
{
    this->x = -1;
    this->y = -1;
    this->z = -1;
}

Position::Position(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Position::Position(const Position& p) {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
}

int Position::getX()
{
    return x;
}

int Position::getY()
{
    return y;
}

int Position::getZ()
{
    return z;
}

void Position::setX(int x)
{
    this->x = x;
}

void Position::setY(int y)
{
    this->y = y;
}

void Position::setZ(int z)
{
    this->z = z;
}

bool Position::isEmpty()
{
    return x == -1 && y == -1 && z == -1;
}

void Position::print()
{
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

bool Position::operator==(const Position& other) const
{
    return (x == other.x) && (y == other.y) && (z == other.z);
}