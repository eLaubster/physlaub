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
    for(auto b : world->bodies) {

        if(b == this) {
            continue;
        }

        bool collided = false;
        for(auto collider : collidedWith) {
            if(b == collider) {
                collided = true;
                break;
            }
        }

        if(collided) {
            continue;
        }

        Shape* s1 = fixture->shape;
        Shape* s2 = b->fixture->shape;

        CircleShape* c1 = dynamic_cast<CircleShape*>(s1);
        CircleShape* c2 = dynamic_cast<CircleShape*>(s2);

        // For circle-circle collisions
        if(s1->checkOverlap(s2)) {
            float m1 = fixture->mass;
            float m2 = b->fixture->mass;

            float dist = b->pos.sub(pos).getMag();
            float overlap = 0.5 * (dist - c1->r - c2->r);

            std::cout << dist << std::endl;
            std::cout << "s1: " << c1->r << std::endl;
            std::cout << "s2: " << c2->r << std::endl;

            pos.x -= overlap*(pos.x - b->pos.x)/dist;
            pos.y -= overlap*(pos.y - b->pos.y)/dist;

            b->pos.x += overlap*(pos.x - b->pos.x)/dist;
            b->pos.y += overlap*(pos.y - b->pos.y)/dist;

            dist = b->pos.sub(pos).getMag();
            Vec2d norm = Vec2d((b->pos.x-pos.x)/dist, (b->pos.y-pos.y)/dist);
            Vec2d tangent = Vec2d(norm.x, -norm.y);

            float dotOrigTan = vel.dot(tangent);
            float dotTargTan = b->vel.dot(tangent);

            float dotOrigNorm = vel.x*norm.x + vel.y*norm.y;
            float dotTargNorm = b->vel.x*norm.x + b->vel.y*norm.y;
            
            std::cout << m1 + m2 << std::endl;
            float p1 = (dotOrigNorm * (m1 - m2) + 2 * m2*dotTargNorm) / (m1+m2);
            float p2 = (dotTargNorm * (m2 - m1) + 2 * m1*dotOrigNorm) / (m1+m2);

            vel.x = tangent.x * dotOrigTan + norm.x * p1;
            vel.y = tangent.y * dotOrigTan + norm.y * p1;
            b->vel.x = tangent.x * dotTargTan + norm.x * p2;
            b->vel.y = tangent.y * dotTargTan + norm.y * p2;

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
