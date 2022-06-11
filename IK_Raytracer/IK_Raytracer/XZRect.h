#pragma once
#include "Hitable.h"
class XZRect : public Hitable
{
public:
	float x0, x1, z0, z1, k;
	bool isFlipped = false;
	Material* mp;

	XZRect() {}
	XZRect(float _x0, float _x1, float _z0, float _z1, float _k, Material* mat, bool isFlip) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat), isFlipped(isFlip) {};

	virtual bool hit(const Ray& r, float t0, float t1, hitRecord& rec) const
	{
		float t = (k - r.origin().y()) / r.direction().y();
		if (t < t0 || t > t1)
			return false;
		float x = r.origin().x() + t * r.direction().x();
		float z = r.origin().z() + t * r.direction().z();

		if (x < x0 || x > x1 || z < z0 || z > z1)
			return false;

		rec.u = (x - x0) / (x1 - x0);
		rec.v = (z - z0) / (z1 - z0);
		rec.t = t;
		rec.materialPtr = mp;
		rec.p = r.pointAtParameter(t);

		if (isFlipped)
			rec.normal = vec3(0, 1, 0);
		else
			rec.normal = vec3(0, -1, 0);

		return true;
	}
};

