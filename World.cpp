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

void World::update(double timeStep, int divisions) {

    for(int i = 0; i < divisions; i++) {
        for (auto b: bodies) {
            double x = b->pos.x;
            double y = b->pos.y;

           double r = b->fixture->shape->r;

            if(r) {
                if (x > 1280 - r) {
                    b->vel.x *= -1;
                } else if (x < r) {
                    b->vel.x *= -1;
                }

                if (y > 720 - r) {
                    b->vel.y *= -1;
                } else if (y < r) {
                    b->vel.y *= -1;
                }
            }

            b->acc.add(gravity);
            b->update(timeStep/(double)divisions);
        }
    }
}