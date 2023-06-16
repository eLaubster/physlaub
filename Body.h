//
// Created by Evan Laube on 4/28/23.
//

#ifndef PHYSLAUB_BODY_H
#define PHYSLAUB_BODY_H


#include "Vec2d.h"
#include "Fixture.h"
#include <vector>

class World;

class Body {

public:
    static const int STATIC = 0;
    static const int KINEMATIC = 1;

    int type = 0;

    Vec2d pos = Vec2d(0,0);
    Vec2d vel = Vec2d(0,0);
    Vec2d acc = Vec2d(0,0);
    float a = 0;

    std::vector<Body*> collidedWith = {};

    Fixture* fixture;

    Body(double x, double y, double a);

    void addForce(Vec2d f);
    void collide();
    void update(double timeStep);
    void setType(int type);
    void addFixture(Fixture *fixture);
    void setWorld(World *world);

private:
    World* world;

};


#endif //PHYSLAUB_BODY_H
