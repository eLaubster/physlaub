//
// Created by Evan Laube on 6/17/23.
//

#ifndef PHYSLAUB_RECTSHAPE_H
#define PHYSLAUB_RECTSHAPE_H

#import "Shape.h"


class RectShape : public Shape{

public:
    RectShape(double w, double h);

    double h;
    double w;

    bool checkOverlap(Shape* s) override;
    bool pointInside(Vec2d point) override;
    Vec2d * getVertexes();
};


#endif //PHYSLAUB_RECTSHAPE_H
