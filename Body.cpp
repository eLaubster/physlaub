//
// Created by Evan Laube on 4/28/23.
//

#include <iostream>
#include "Body.h"
#include "World.h"
#include "CircleShape.h"
using namespace std;

Body::Body(double x, double y, double a) {
    pos = Vec2d(x,y);
    vel = Vec2d(0,0);
    acc = Vec2d(0,0);

    this->a = a;
}

void Body::addForce(Vec2d f) {
    acc.x = f.x/fixture->mass;
    acc.y = f.y/fixture->mass;
}

// Step the body forward in time
void Body::update(double timeStep) {
    collide();

    // Only move position if the body is of type KINEMATIC
    if(type == KINEMATIC) {
        vel = vel.add(acc.scalarMult(timeStep));
        pos = pos.add(vel.scalarMult(timeStep));
        acc = Vec2d(0, 0);
    }

    if(!collidedWith.empty()) {
        collidedWith = {};
    }
}

void Body::collide() {
    bool bp = false;
    for(auto b2 : world->bodies) {

        // Do not collide with self
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
//            cout << "Collision: " << endl;

            double m1 = b1->fixture->mass;
            double m2 = b2->fixture->mass;

//            cout << "\t-> Total Initial Momentum: " << (b1->vel.x * m1) + (b2->vel.x * m2) << endl;

            // Calculate distance between circles
            double dist = b2->pos.sub(b1->pos).getMag();
            // Calculate the total distance overlapping between the two circles
            double overlap = 0.5 * (dist - c1->r - c2->r);

            // Calculate the unit vector between the two circles
            double normx = (b2->pos.x - b1->pos.x) / dist;
            double normy = (b2->pos.y - b1->pos.y) / dist;

            // TODO: Make circles push away from eachother along velocity vectors instead of shortest path for more accurate collisions.
            // Calculate static overlap collision to push bodies apart from eachother so they do not coincide
            b1->pos.x -= overlap * (pos.x - b2->pos.x) / dist;
            b1->pos.y -= overlap * (pos.y - b2->pos.y) / dist;
            b2->pos.x += overlap * (pos.x - b2->pos.x) / dist;
            b2->pos.y += overlap * (pos.y - b2->pos.y) / dist;

            // Calculate the tangent along the two intersecting edges of the circles
            Vec2d norm = Vec2d(normx, normy);
            Vec2d tang = Vec2d(normy, -normx);

            // Dot products of the velocity vectors of both bodies and the normailzied tangent
            double dptang1 = b1->vel.dot(tang);
            double dptang2 = b2->vel.dot(tang);

            // Dot products of the velocity vectors of both bodies and the normal
            double dpnorm1 = b1->vel.dot(norm);
            double dpnorm2 = b2->vel.dot(norm);

            // Conservation of momentum applied in 1D along the normal vector
            // Does not need to apply along the tangent vector
            double p2 = (m1 * dpnorm1 + m2 * dpnorm2 + m1 * (dpnorm1 - dpnorm2)) / (m1 + m2); // (m1v1 + m2v2 + m1(v1-v2)) / (m1 + m2) = u2
            double p1 = p2 - (dpnorm1 - dpnorm2);                                             // u1 = u2 - (v1 - v2)

            // Set new velocity values to bodies
            b1->vel.x = dptang1 * tang.x + p1 * norm.x;
            b1->vel.y = dptang1 * tang.y + p1 * norm.y;
            b2->vel.x = dptang2 * tang.x + p2 * norm.x;
            b2->vel.y = dptang2 * tang.y + p2 * norm.y;

//            cout << "\t-> Total Final Momentum: " << (b1->vel.x * m1) + (b2->vel.x * m2) << endl;
//            cout << endl;
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
