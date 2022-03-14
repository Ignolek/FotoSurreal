#pragma once
#include "Vector.h"

class Plane
{
private:
    float a, b, c, d;        //the (a, b, c, d) in a*x + b*y + c*z + d = 0.

public:
    Plane();
    Plane(const Plane& P);
    Plane(float a, float b, float c, float d);

    Vector intersectLine(const Vector V1, const Vector V2) const;        //determines the intersect of the line defined by the points V1 and V2 with the plane.
};

