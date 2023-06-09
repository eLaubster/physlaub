//
// Created by Evan Laube on 4/28/23.
//

#ifndef PHYSLAUB_SHAPE_H
#define PHYSLAUB_SHAPE_H

#include "Vec2d.h"

class Fixture;
class CircleShape;

class Shape {
public:
    virtual ~Shape() {};
    virtual bool checkOverlap(Shape* s) = 0;
    virtual bool pointInside(Vec2d point) = 0;
    virtual void setFixture(Fixture* fixture);
    double r;
protected:
    Fixture* fixture = nullptr;
};


#endif //PHYSLAUB_SHAPE_H
