//
// Created by Evan Laube on 4/28/23.
//

#ifndef PHYSLAUB_VEC2D_H
#define PHYSLAUB_VEC2D_H

class Vec2d {
public:
    float x;
    float y;

    Vec2d(float x, float y);

    float getMag();
    Vec2d add(Vec2d b);
    Vec2d sub(Vec2d b);
    Vec2d scalarMult(float s);
    Vec2d normalize();
    float dot(Vec2d b);
};


#endif //PHYSLAUB_VEC2D_H
