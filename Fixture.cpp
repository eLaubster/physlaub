//
// Created by Evan Laube on 4/28/23.
//

#include "Fixture.h"
#include "Body.h"
#include "Vec2d.h"

Fixture::Fixture(Shape* shape) {
    this->shape = shape;
    shape->setFixture(this);
}

void Fixture::setBody(Body *body) {
    this->body = body;
}

Vec2d Fixture::getPos() {
    return body->pos;
}

double Fixture::getAngle() {
    return body->a;
}

const Shape* Fixture::getShape() {
    return shape;
}
