#pragma once
#include "vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Material.h"

class Plane : public Hitable
{
public:
    float a, b, c, d;        //the (a, b, c, d) in a*x + b*y + c*z + d = 0
    Material* planeMat;

    Plane();
    Plane(const Plane& P);
    Plane(float a, float b, float c, float d, Material* planeMaterial);
    Plane(const vec3& Pt, const vec3& V1, const vec3& V2, Material* planeMaterial);

    static Plane ConstructFromPointNormal(const vec3& Pt, const vec3& Normal);
    static Plane ConstructFromPointVectors(const vec3& Pt, const vec3& V1, const vec3& V2);

    vec3 intersectLine(const vec3 V1, const vec3 V2) const;        //determines the intersect of the line defined by the points V1 and V2 with the plane.
    bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const;
};