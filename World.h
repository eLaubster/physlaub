//
// Created by Evan Laube on 4/27/23.
//

#ifndef PHYSLAUB_WORLD_H
#define PHYSLAUB_WORLD_H

#include <vector>
#include "Vec2d.h"
#include "Body.h"

class World {
public:
    World();
    void setGravity(float x, float y);
    void update(float timeStep, int divisions);
    void addBody(Body* b);
    std::vector<Body*> bodies;

private:
    Vec2d gravity = Vec2d(0,0);
};


#endif //PHYSLAUB_WORLD_H
