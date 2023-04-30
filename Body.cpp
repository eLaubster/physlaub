//
// Created by Evan Laube on 4/28/23.
//

#include <iostream>
#include <cmath>
#include <vector>
#include "Body.h"
#include "World.h"
#include "CircleShape.h"

Body::Body(float x, float y, float a) {
    pos = Vec2d(x,y);
    vel = Vec2d(0,0);
    acc = Vec2d(0,0);

    this->a = a;
}

void Body::addForce(Vec2d f) {
    acc.x = f.x/fixture->mass;
    acc.y = f.y/fixture->mass;
}

void Body::update(float timeStep) {
    if(type == KINEMATIC) {
        vel = vel.add(acc.scalarMult(timeStep));
        pos = pos.add(vel.scalarMult(timeStep));
        acc = Vec2d(0, 0);
    }

    if(collidedWith.size() > 0) {
        collidedWith = {};
    }
}

void Body::collide() {
    for(auto b2 : world->bodies) {

        if(b2 == this) {
            continue;
        }

        bool collided = false;
        for(auto collider : collidedWith) {
            if(b2 == collider) {
                collided = true;
                break;
            }
        }

        if(collided) {
            continue;
        }

        Body* b1 = this;

        Shape* s1 = b1->fixture->shape;
        Shape* s2 = b2->fixture->shape;

        CircleShape* c1 = dynamic_cast<CircleShape*>(s1);
        CircleShape* c2 = dynamic_cast<CircleShape*>(s2);

        // For circle-circle collisions
        if(s1->checkOverlap(s2)) {

            float m1 = b1->fixture->mass;
            float m2 = b2->fixture->mass;

            float dist = b2->pos.sub(b1->pos).getMag();
            float overlap = 0.5 * (dist - c1->r - c2->r);

            b1->pos.x -= overlap * (pos.x - b2->pos.x) / dist;
            b1->pos.y -= overlap * (pos.y - b2->pos.y) / dist;
            b2->pos.x += overlap * (pos.x - b2->pos.x) / dist;
            b2->pos.y += overlap * (pos.y - b2->pos.y) / dist;

            float normx = (b2->pos.x - b1->pos.x) / dist;
            float normy = (b2->pos.y - b1->pos.y) / dist;

            Vec2d norm = Vec2d(normx, normy);
            Vec2d tang = Vec2d(norm.y, -norm.x);

            float normDp1 = b1->vel.dot(norm);
            float normDp2 = b2->vel.dot(norm);

            float p1 = (normDp1 * (m1-m2) + 2 * m2 * normDp2) / (m1+m2);
            float p2 = (normDp2 * (m2-m1) + 2 * m1 * normDp1) / (m1+m2);

            b1->vel.x = tang.x * b1->vel.dot(tang) + norm.x * p1;
            b1->vel.y = tang.y * b1->vel.dot(tang) + norm.y * p1;

            b2->vel.x = tang.x * b2->vel.dot(tang) + norm.x * p2;
            b2->vel.y = tang.y * b2->vel.dot(tang) + norm.y * p2;
        }
    }
}

void Body::setType(int type) {
    this->type = type;
}

void Body::setWorld(World *world) {
    this->world = world;
}

void Body::addFixture(Fixture *fixture) {
    this->fixture = fixture;
    fixture->setBody(this);
}
