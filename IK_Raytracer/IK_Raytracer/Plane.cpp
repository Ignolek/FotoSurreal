#include "Plane.h"

Plane::Plane()
{

}

Plane::Plane(const Plane& P)
{
    a = P.a;
    b = P.b;
    c = P.c;
    d = P.d;
}

Plane::Plane(float a, float b, float c, float d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

vec3 Plane::intersectLine(const vec3 V1, const vec3 V2) const
{
    vec3 Diff = V1 - V2;
    float Denominator = a * Diff.e[0] + b * Diff.e[1] + c * Diff.e[2];
    if (Denominator == 0.0f)
    {
        return (V1 + V2) * 0.5f;
    }
    float u = (a * V1.e[0] + b * V1.e[1] + c * V1.e[2] + d) / Denominator;

    return (V1 + (V2 - V1)*u);
}