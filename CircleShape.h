//
// Created by Evan Laube on 4/28/23.
//

#ifndef PHYSLAUB_CIRCLESHAPE_H
#define PHYSLAUB_CIRCLESHAPE_H

#include "Shape.h"

class CircleShape : public Shape {
public:
    double r;

    CircleShape(float r);

    bool checkOverlap(Shape* s) override;
};


#endif //PHYSLAUB_CIRCLESHAPE_H
