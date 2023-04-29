//
// Created by Evan Laube on 4/28/23.
//

#include "Shape.h"
#include "Fixture.h"
#include "Vec2d.h"
#include "CircleShape.h"
#include <iostream>

void Shape::setFixture(Fixture* fixture) {
    this->fixture = fixture;
}

//bool Shape::checkOverlap(Shape* s) {
//    CircleShape* c1 = dynamic_cast<CircleShape*>(this);
//    CircleShape* c2 = dynamic_cast<CircleShape*>(s);
//
//    if (c1 && c2) {
//        Vec2d pos1 = fixture->getPos();
//        Vec2d pos2 = s->fixture->getPos();
//        Vec2d diff = pos1.sub(pos2);
//        float dist = diff.getMag();
//        return (dist < (c1->r + c2->r));
//    }
//    return false;
//}
