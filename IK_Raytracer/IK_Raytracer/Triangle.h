#pragma once
#include "vec3.h"
#include "Ray.h"
#include "Hitable.h"

class Triangle : public Hitable
{
public:
	vec3 tA, tB, tC;
	bool _hit = false;

	double distance = 0;

	Triangle() : tA(1, 0, 0), tB(0, 1, 0), tC(0, 0, 1){}
	Triangle(const vec3 _a, const vec3 _b, const vec3 _c) : tA(_a), tB(_b), tC(_c){}
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

		if (a == 0)
		{
			return -1;
		}
		else
		{
			double b = dot(normal, ray.origin() + (normal * -distance)); // moze to?
			double distanceToPlane = -1 * b / a;

			double Qx = rayDirection.e[0] * distanceToPlane + ray.origin().e[0]; // moze to?
			double Qy = rayDirection.e[1] * distanceToPlane + ray.origin().e[1]; // moze to?
			double Qz = rayDirection.e[2] * distanceToPlane + ray.origin().e[2]; // moze to?

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

			if (test1 >= 0 && test2 >= 0 && test3 >= 0)//(test1 >= tMin && test2 >= tMin && test3 >= tMin && test1 <= tMax && test2 <= tMax && test3 <= tMax)
			{
				// inside triangle
				rec.t = -1 * b / a;
				rec.p = ray.pointAtParameter(rec.t);
				rec.normal = normal;

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