#pragma once
#include "Hitable.h"
class YZRect : public Hitable
{
public:
	float y0, y1, z0, z1, k;
	bool isFlipped = false;
	Material* mp;

	YZRect() {}
	YZRect(float _y0, float _y1, float _z0, float _z1, float _k, Material* mat, bool isFlip) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat), isFlipped(isFlip) {};

	virtual bool hit(const Ray& r, float t0, float t1, hitRecord& rec) const
	{
		float t = (k - r.origin().x()) / r.direction().x();
		if (t < t0 || t > t1)
			return false;
		float y = r.origin().y() + t * r.direction().y();
		float z = r.origin().z() + t * r.direction().z();

		if (y < y0 || y > y1 || z < z0 || z > z1)
			return false;

		rec.u = (y - y0) / (y1 - y0);
		rec.v = (z - z0) / (z1 - z0);
		rec.t = t;
		rec.materialPtr = mp;
		rec.p = r.pointAtParameter(t);

		if (isFlipped)
			rec.normal = vec3(1, 0, 0);
		else
			rec.normal = vec3(-1, 0, 0);

		return true;
	}
};

