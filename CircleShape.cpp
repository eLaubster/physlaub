//
// Created by Evan Laube on 4/28/23.
//

#include "Vec2d.h"
#include "Fixture.h"
#include "Body.h"
#include "CircleShape.h"
#include "RectShape.h"

#include <iostream>
#include <typeinfo>
#include <cmath>
using namespace std;

CircleShape::CircleShape(float r) {
    this->r = r;
}

// Check if circle is overlapping other shape
bool CircleShape::checkOverlap(Shape* s) {
    CircleShape* cs = dynamic_cast<CircleShape*>(s);
    RectShape* rs = dynamic_cast<RectShape*>(s);


    if (cs) {
        // If distance between two circles is less than the sum of their radius, they are colliding
        Vec2d pos1 = fixture->getPos();
        Vec2d pos2 = cs->fixture->getPos();
        Vec2d diff = pos1.sub(pos2);
        return(pow(diff.x, 2) + pow(diff.y, 2) < pow(this->r + cs->r, 2));
    } else if(rs) {

    }
    return false;
}

// Check if a point falls inside the circle
bool CircleShape::pointInside(Vec2d point) {
    return false;
}
