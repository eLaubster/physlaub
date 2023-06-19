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

Vec2d *RectShape::getVertexes() {
    Vec2d *vertexes = new Vec2d[4];

    Vec2d pos = fixture->getPos();
    double hyp = sqrt(pow(w / 2, 2) + pow(h / 2, 2));

    double aStart = (atan(h / w)) * (180 / M_PI);
    float angles[4];
    angles[0] = aStart;
    angles[1] = 180 - aStart;
    angles[2] = angles[0] + 180;
    angles[3] = angles[1] + 180;

    for (int i = 0; i < 4; i++) {
        double aInc = aStart;


        // TODO: clean up the logic in these if statements
        // They work but they are messy
        if(i % 2 == 0)
            aInc = 180-aStart;

        double a = aInc + fixture->getAngle();
        if(i > 1)
            a += 180;

        double px = pos.x + hyp * cos((M_PI * a) / 180);
        double py = pos.y + hyp * sin((M_PI * a) / 180);

        // std::cout << aStart << ": (" << px << ", " << py << ")" << std::endl;

        vertexes[i] = Vec2d(px, py);
    }

    return vertexes;
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

        getVertexes();

        std::cout << "In range for collision" << std::endl;

        return false;
    } else if (cs) {
        return false;
    }

    return false;
}

bool RectShape::pointInside(Vec2d point) {
    return false;
}
