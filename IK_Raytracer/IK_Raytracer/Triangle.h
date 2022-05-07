#pragma once
#include "vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Material.h"

#define MINUS_ZERO -0.00001 

class Triangle : public Hitable
{
public:
	vec3 tA, tB, tC;
	bool _hit = false;
	vec3 color;

	double distance = 0;
	Material* triangleMaterial;

	Triangle() : tA(1, 0, 0), tB(0, 1, 0), tC(0, 0, 1){}
	Triangle(const vec3 _a, const vec3 _b, const vec3 _c, vec3 col, Material* triMaterial) : tA(_a), tB(_b), tC(_c), color(col), triangleMaterial(triMaterial){}
	~Triangle();

	vec3 getTriangleNormal() const
	{
		vec3 normal = vec3(0, 0, 0);
		vec3 CA(tC.e[0] - tA.e[0],
				tC.e[1] - tA.e[1],
				tC.e[2] - tA.e[2]);

		vec3 BA(tB.e[0] - tA.e[0],
				tB.e[1] - tA.e[1],
				tB.e[2] - tA.e[2]);

		normal = normalize(cross(CA, BA));

		return normal;
	}

	double getTriangleDistance() const
	{
		vec3 normal = vec3(0, 0, 0);
		double distance = 0;

		normal = getTriangleNormal();
		distance = dot(normal, tA);

		return distance;
	}

	virtual vec3 getNormalAt(vec3 point) const
	{
		vec3 normal = vec3(0, 0, 0);
		normal = getTriangleNormal();

		return normal;
	}

	bool hit(const Ray& ray, float tMin, float tMax, hitRecord& rec) const
	{
		vec3 rayDirection = ray.direction();
		vec3 rayOrigin = ray.origin();

		vec3 normal = vec3(0, 0, 0);
		double distance = 0;

		normal = getTriangleNormal();
		distance = getTriangleDistance();

		double a = dot(rayDirection, normal);

		if (a <= MINUS_ZERO)
		{
			return false;
		}
		else
		{
			double b = dot(normal, ray.origin() + (normal * -distance));
			double distanceToPlane = -1.0f * b / a;

			double Qx = rayDirection.e[0] * distanceToPlane + ray.origin().e[0];
			double Qy = rayDirection.e[1] * distanceToPlane + ray.origin().e[1];
			double Qz = rayDirection.e[2] * distanceToPlane + ray.origin().e[2];

			vec3 Q(Qx, Qy, Qz);

			// [CAxQA] * n >= 0
			vec3 CA(tC.e[0] - tA.e[0],
					tC.e[1] - tA.e[1],
					tC.e[2] - tA.e[2]);

			vec3 QA(Q.e[0] - tA.e[0],
					Q.e[1] - tA.e[1],
					Q.e[2] - tA.e[2]);

			double test1 = dot(cross(CA, QA), normal);

			// [BCxQC] * n >= 0
			vec3 BC(tB.e[0] - tC.e[0],
					tB.e[1] - tC.e[1],
					tB.e[2] - tC.e[2]);

			vec3 QC(Q.e[0] - tC.e[0],
					Q.e[1] - tC.e[1],
					Q.e[2] - tC.e[2]);

			double test2 = dot(cross(BC, QC), normal);

			// [ABxQB] * n >= 0
			vec3 AB(tA.e[0] - tB.e[0],
					tA.e[1] - tB.e[1],
					tA.e[2] - tB.e[2]);

			vec3 QB(Q.e[0] - tB.e[0],
					Q.e[1] - tB.e[1],
					Q.e[2] - tB.e[2]);

			double test3 = dot(cross(AB, QB), normal);

			if (test1 >= tMin && test2 >= tMin && test3 >= tMin && test1 <= tMax && test2 <= tMax && test3 <= tMax)//(test1 >= PLUS_ZERO && test2 >= PLUS_ZERO && test3 >= PLUS_ZERO)//(test1 >= tMin && test2 >= tMin && test3 >= tMin && test1 <= tMax && test2 <= tMax && test3 <= tMax)
			//if (test1 >= PLUS_ZERO && test2 >= PLUS_ZERO && test3 >= PLUS_ZERO)
			{
				// inside triangle
				rec.t = -1 * b / a;
				rec.p = Q;
				rec.normal = normal;
				rec.hitColor = color;
				rec.materialPtr = triangleMaterial;

				return true;
			}
			else
			{
				// outside triangle
				return false;
			}
		}
	}
};