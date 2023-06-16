//
// Created by Evan Laube on 4/28/23.
//

#include "Vec2d.h"
#include <cmath>

Vec2d::Vec2d(double x, double y) {
    this->x = x;
    this->y = y;
}

Vec2d Vec2d::add(Vec2d b) {
    this->x += b.x;
    this->y += b.y;
    return(Vec2d(x,y));
}

Vec2d Vec2d::sub(Vec2d b) {
    return(Vec2d(x-b.x,y-b.y));
}

Vec2d Vec2d::scalarMult(double s) {
    return Vec2d(x*s, y*s);
}

float Vec2d::getMag() {
    return sqrt((pow(x, 2) + pow(y, 2)));
}

Vec2d Vec2d::normalize() {
    float mag = getMag();
    return(Vec2d(x/mag, y/mag));
}

float Vec2d::dot(Vec2d b) {
    return x*b.x + y*b.y;
}