//
// Created by Evan Laube on 4/28/23.
//

#ifndef PHYSLAUB_FIXTURE_H
#define PHYSLAUB_FIXTURE_H

#include "Shape.h"
class Vec2d;

class Body;
class Shape;

class Fixture {

public:
    Shape* shape;
    float mass = 5;
    float friction = 0; // 0-1
    float restitution = 1; // 0-1

    Fixture(Shape* shape);

    void setBody(Body *body);

    Vec2d getPos();
    double getAngle();
    const Shape* getShape();

private:
    Body* body;


};


#endif //PHYSLAUB_FIXTURE_H
