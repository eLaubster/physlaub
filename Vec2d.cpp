//
// Created by Evan Laube on 4/28/23.
//

#include "Vec2d.h"
#include <cmath>

Vec2d::Vec2d() {
    this->x = 0;
    this->y = 0;
}

Vec2d::Vec2d(double x, double y) {
    this->x = x;
    this->y = y;
}

// Returns the sum of two Vec2d Vectors
Vec2d Vec2d::add(Vec2d b) {
    this->x += b.x;
    this->y += b.y;
    return(Vec2d(x,y));
}

// Returns the difference of two Vec2d Vectors
Vec2d Vec2d::sub(Vec2d b) {
    return(Vec2d(x-b.x,y-b.y));
}

// Returns a vector multiplied by a scalar
Vec2d Vec2d::scalarMult(double s) {
    return Vec2d(x*s, y*s);
}

// Returns the magnitude of a vector
double Vec2d::getMag() {
    return sqrt((pow(x, 2) + pow(y, 2)));
}

// Returns a vector in the same direction with a magnitude of 1
Vec2d Vec2d::normalize() {
    double mag = getMag();
    return(Vec2d(x/mag, y/mag));
}

// Returns the dot product of two vectors
double Vec2d::dot(Vec2d b) {
    return x*b.x + y*b.y;
}
