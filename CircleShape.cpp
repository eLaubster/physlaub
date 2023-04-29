//
// Created by Evan Laube on 4/28/23.
//

#include "Vec2d.h"
#include "Fixture.h"
#include "Body.h"
#include "CircleShape.h"

#include <iostream>
#include <cmath>
using namespace std;

CircleShape::CircleShape(float r) {
    this->r = r;
}

bool CircleShape::checkOverlap(Shape* s) {

    CircleShape* other = dynamic_cast<CircleShape*>(s);

    if (other) {
        Vec2d pos1 = fixture->getPos();
        Vec2d pos2 = other->fixture->getPos();
        Vec2d diff = pos1.sub(pos2);
        return(pow(diff.x, 2) + pow(diff.y, 2) < pow(this->r + other->r, 2));
    }
    return false;
}
