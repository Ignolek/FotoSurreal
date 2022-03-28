#pragma once
#include "vec3.h"

class Plane
{
private:
    float a, b, c, d;        //the (a, b, c, d) in a*x + b*y + c*z + d = 0.

public:
    Plane();
    Plane(const Plane& P);
    Plane(float a, float b, float c, float d);

    vec3 intersectLine(const vec3 V1, const vec3 V2) const;        //determines the intersect of the line defined by the points V1 and V2 with the plane.
};

