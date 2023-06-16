//
// Created by Evan Laube on 4/27/23.
//

#include "World.h"
#include "CircleShape.h"
#include <iostream>
using namespace std;

World::World() {
}

void World::setGravity(float x, float y) {
    gravity = Vec2d(x, y);
}

void World::addBody(Body* b) {
    b->setWorld(this);
    bodies.push_back(b);
}

void World::update(float timeStep, int divisions) {

    for(int i = 0; i < divisions; i++) {
        for (auto b: bodies) {
            float x = b->pos.x;
            float y = b->pos.y;
            float r = dynamic_cast<CircleShape*>(b->fixture->shape)->r;

            if(x > 1280 - r) {
                b->vel.x *= -1;
            } else if(x < r) {
                b->vel.x *= -1;
            }

            if(y > 720 - r) {
                b->vel.y *= -1;
            } else if(y < r) {
                b->vel.y *= -1;
            }

            b->acc.add(gravity);
            b->update(timeStep/divisions);
        }
    }
}