#pragma once
#include "Hitable.h"
class XYRect: public Hitable
{
public:
	float x0, x1, y0, y1, k;

	bool isFlipped = false;
	Material* mp;

	XYRect(){}
	XYRect(float _x0, float _x1, float _y0, float _y1, float _k, Material* mat, bool isFlip) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat), isFlipped(isFlip) {};

	virtual bool hit(const Ray& r, float t0, float t1, hitRecord& rec) const
	{
		float t = (k - r.origin().z()) / r.direction().z();
		if (t < t0 || t > t1)
			return false;
		float x = r.origin().x() + t * r.direction().x();
		float y = r.origin().y() + t * r.direction().y();

		if (x < x0 || x > x1 || y < y0 || y > y1)
			return false;

		rec.u = (x - x0) / (x1 - x0);
		rec.v = (y - y0) / (y1 - y0);
		rec.t = t;
		rec.materialPtr = mp;
		rec.p = r.pointAtParameter(t);

		if (isFlipped)
			rec.normal = vec3(0, 0, 1);
		else
			rec.normal = vec3(0, 0, -1);

		return true;
	}
};

