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

    // Radius equal to the radius of a circle that circumscribes the rectangle
    this->r = sqrt(pow(h, 2) + pow(w, 2)) / 2.0;
}

// Returns a Vec2d array of points where the verticies of the rectangle are
Vec2d *RectShape::getVertices() {
    Vec2d *vertices = new Vec2d[4];

    // Calculate the distance between the center of rectangle to the outer corner
    Vec2d pos = fixture->getPos();
    double hyp = sqrt(pow(w / 2, 2) + pow(h / 2, 2));

    // Calculate the angle from the center of the rectangle to the top right corner
    double aStart = (atan(h / w)) * (180 / M_PI);

    for (int i = 0; i < 4; i++) {
        double aInc = aStart;

        // TODO: clean up the logic in these if statements
        //  They work but they are messy
        if (i % 2 == 0)
            aInc = 180 - aStart;

        // For the bottom two corners, do the same as the top two but add 180 degrees
        double a = aInc + fixture->getAngle();
        if (i > 1)
            a += 180;

        // Set store positions of rectangle corners into px and py.
        double px = pos.x + hyp * cos((M_PI * a) / 180);
        double py = pos.y + hyp * sin((M_PI * a) / 180);

//        std::cout << aStart << ": (" << px << ", " << py << ")" << std::endl;
        vertices[i] = Vec2d(px, py);
    }

    return vertices;
}

// Check if the shape overlaps with another shape
bool RectShape::checkOverlap(Shape *s) {

    CircleShape *cs = dynamic_cast<CircleShape *>(s);
    RectShape *rs = dynamic_cast<RectShape *>(s);


    if (rs) { // If shape to check is a RectangleShape
        Vec2d pos1 = this->fixture->getPos();
        Vec2d pos2 = rs->fixture->getPos();
        Vec2d dif = pos1.sub(pos2);

        // TODO: Check if it is faster to calculate the distance between rectangles to determine
        //  if they are in range for collision, or check all rectangles with the pointInside()
        //  method regardless of their distance

        // If the distance between the two rectanges is less than the sum of their two hypotenuse
        if (pow(dif.x, 2) + pow(dif.y, 2) > pow((r + rs->r), 2))
            return false;

        // Store vertices of both rectangle a and b
        Vec2d * aVerts = getVertices();
        Vec2d * bVerts = rs->getVertices();

        // Check if any of the verticies fall inside the other shape
        int vertCount = 4;
        for(int i = 0; i < vertCount; i++) {
            if(pointInside(bVerts[i]) || rs->pointInside(aVerts[i])) {
                return true;
            }
        }

        // Check if the center of the shape falls inside the other shape
        if(pointInside(rs->fixture->getPos())) {
            return true;
        }

        return false;
    } else if (cs) { // If shape to check is a CircleShape
        return false;
    }

    return false;
}

// Check if a point is inside the shape
bool RectShape::pointInside(Vec2d point) {

    bool odd = false;

    Vec2d *vertices = getVertices();
    // TODO: find length from vertices array instead of hard coding
    int len = 4;
    // Cast a ray infinitely right and count how many sides it passes through
    // If it passes an odd number then the point is inside the shape
    for (int i = 0, j = len - 1; i < len; j = i++) {
        if (((vertices[i].y > point.y) != (vertices[j].y > point.y)) &&
            (point.x < (vertices[j].x - vertices[i].x) * (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) +
                       vertices[i].x))
            odd = !odd;
    }

    return odd;
}
