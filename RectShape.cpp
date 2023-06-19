//
// Created by Evan Laube on 6/17/23.
//

#include "RectShape.h"
#include "CircleShape.h"
#include "Vec2d.h"
#include "Fixture.h"
#include <cmath>
#include <iostream>

RectShape::RectShape(double w, double h) {
    this->h = h;
    this->w = w;

    this->r = sqrt(pow(h, 2) + pow(w, 2)) / 2.0;
}

Vec2d *RectShape::getVertices() {
    Vec2d *vertices = new Vec2d[4];

    Vec2d pos = fixture->getPos();
    double hyp = sqrt(pow(w / 2, 2) + pow(h / 2, 2));

    double aStart = (atan(h / w)) * (180 / M_PI);

    for (int i = 0; i < 4; i++) {
        double aInc = aStart;

        // TODO: clean up the logic in these if statements
        // They work but they are messy
        if (i % 2 == 0)
            aInc = 180 - aStart;

        double a = aInc + fixture->getAngle();
        if (i > 1)
            a += 180;

        double px = pos.x + hyp * cos((M_PI * a) / 180);
        double py = pos.y + hyp * sin((M_PI * a) / 180);

//        std::cout << aStart << ": (" << px << ", " << py << ")" << std::endl;
        vertices[i] = Vec2d(px, py);
    }

    return vertices;
}


bool RectShape::checkOverlap(Shape *s) {

    CircleShape *cs = dynamic_cast<CircleShape *>(s);
    RectShape *rs = dynamic_cast<RectShape *>(s);

    if (rs) {

        Vec2d pos1 = this->fixture->getPos();
        Vec2d pos2 = rs->fixture->getPos();
        Vec2d dif = pos1.sub(pos2);

        if (pow(dif.x, 2) + pow(dif.y, 2) > pow((r + rs->r), 2))
            return false;

        Vec2d * aVerts = getVertices();
        Vec2d * bVerts = rs->getVertices();

        int vertCount = 4;
        for(int i = 0; i < vertCount; i++) {
            if(pointInside(bVerts[i]) || rs->pointInside(aVerts[i])) {
                return true;
            }
        }

        if(pointInside(rs->fixture->getPos())) {
            return true;
        }

        return false;
    } else if (cs) {
        return false;
    }

    return false;
}

bool RectShape::pointInside(Vec2d point) {

    bool odd = false;

    Vec2d *vertices = getVertices();
    // TODO: find length from vertices array instead of hard coding
    int len = 4;
    for (int i = 0, j = len - 1; i < len; j = i++) {
        if (((vertices[i].y > point.y) != (vertices[j].y > point.y)) &&
            (point.x < (vertices[j].x - vertices[i].x) * (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) +
                       vertices[i].x))
            odd = !odd;
    }

    return odd;
}
