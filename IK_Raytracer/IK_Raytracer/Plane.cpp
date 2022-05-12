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

Plane::Plane(float a, float b, float c, float d, Material* planeMaterial) : planeMat(planeMaterial)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

Plane::Plane(const vec3& Pt, const vec3& V1, const vec3& V2, Material* planeMaterial) : planeMat(planeMaterial)
{
    vec3 Normal = cross(V1, V2);
    a = ConstructFromPointNormal(Pt, Normal).a;
    b = ConstructFromPointNormal(Pt, Normal).b;
    c = ConstructFromPointNormal(Pt, Normal).c;
    d = ConstructFromPointNormal(Pt, Normal).d;
}

Plane Plane::ConstructFromPointNormal(const vec3& Pt, const vec3& Normal)
{
    Plane Result;
    vec3 NormalizedNormal = normalize(Normal);
    Result.a = NormalizedNormal.x();
    Result.b = NormalizedNormal.y();
    Result.c = NormalizedNormal.z();
    Result.d = -dot(Pt, NormalizedNormal);
    return Result;
}

Plane Plane::ConstructFromPointVectors(const vec3& Pt, const vec3& V1, const vec3& V2)
{
    vec3 Normal = cross(V1, V2);
    return ConstructFromPointNormal(Pt, Normal);
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

    return (V1 + (V2 - V1) * u);
}

bool Plane::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const
{

    vec3 Diff = r.origin() - r.direction();
    float Denominator = a * Diff.e[0] + b * Diff.e[1] + c * Diff.e[2];
    if (abs(Denominator) > 0.0001f)
    {
        float temp = (a * r.origin().e[0] + b * r.origin().e[1] + c * r.origin().e[2] + d) / Denominator;
        if (temp < tMax && temp > tMin)
        {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = vec3(a, b, c);
            rec.materialPtr = planeMat;

            return true;
        }

        if (temp >= 0) return true;
    }

    return false;
}