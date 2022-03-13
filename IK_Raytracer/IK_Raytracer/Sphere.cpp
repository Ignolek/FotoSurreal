#include "Sphere.h"

Sphere::Sphere() : coords(0,0,0), r(0) {}

Sphere::Sphere(Vector coordinates, float r)
{
	this->coords = coordinates;
	this->r = r;
}

int Sphere::intersect(Ray& a_Ray, float& a_Dist)
{
	Vector v = a_Ray.getOrigin() - this->coords;
	float b = -v.dotProduct(a_Ray.getDirection());
	float det = (b * b) - v.dotProduct(v) + this->r;
	int retval = 0;
	if (det > 0)
	{
		det = sqrtf(det);
		float i1 = b - det;
		float i2 = b + det;
		if (i2 > 0)
		{
			if (i1 < 0)
			{
				if (i2 < a_Dist)
				{
					a_Dist = i2;
					retval = 1;
					// retval = INPRIM; what's inprim?
				}
			}
			else
			{
				if (i1 < a_Dist)
				{
					a_Dist = i1;
					retval = 2;
				}
			}
		}
	}
	return retval;
}
