//
// Created by Evan Laube on 4/27/23.
//

#include "World.h"
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

void World::update(float timeStep) {

    for(auto b : bodies) {
        b->collide();
    }

    for(auto b : bodies) {
        b->acc.add(gravity);
        b->update(timeStep);
    }
}