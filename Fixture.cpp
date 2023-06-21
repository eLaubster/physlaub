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

// Sets the body the fixture is attached to
void Fixture::setBody(Body *body) {
    this->body = body;
}

// Refer to body pointer and get position
Vec2d Fixture::getPos() {
    return body->pos;
}

// Refer to body pointer and get angle
double Fixture::getAngle() {
    return body->a;
}

// Get the shape attached to the fixture
const Shape* Fixture::getShape() {
    return shape;
}
