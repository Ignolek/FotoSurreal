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

Vector Plane::intersectLine(const Vector V1, const Vector V2) const
{
    Vector Diff = V1 - V2;
    float Denominator = a * Diff.x + b * Diff.y + c * Diff.z;
    if (Denominator == 0.0f)
    {
        return (V1 + V2) * 0.5f;
    }
    float u = (a * V1.x + b * V1.y + c * V1.z + d) / Denominator;

    return (V1 + (V2 - V1)*u);
}