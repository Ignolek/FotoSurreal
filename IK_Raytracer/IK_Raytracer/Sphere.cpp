#include "Sphere.h"

Sphere::Sphere() : coords(0,0,0), radius(0) {}

Sphere::Sphere(Vector coordinates, float r)
{
	this->coords = coordinates;
	this->radius = r;
}

float* Sphere::intersect(Ray& ray, float& dist)
{
	//obliczamy r�wnanie kwadratowe
	Vector v = ray.getOrigin() - this->coords;
	float a = ray.getDirection().dotProduct(ray.getDirection());
	float b = 2.0 * v.dotProduct(ray.getDirection());
	float c = v.dotProduct(v) - (this->radius * this->radius);
	float u[2];
	//obliczamy wyr�nik kwadratowy
	float discriminant = b * b - 4 * a * c;
	//zwracamy lokacje przeci�cia
	if (discriminant > 0.0)
	{
		const float root = sqrt(discriminant);
		const float denom = 2.0 * a;

		u[0] = (-b + root) / denom;
		u[1] = (-b - root) / denom;
	}
	else if (discriminant = 0.0)
	{
		const float denom = 2.0 * a;

		u[0] = (-b) / denom;
		u[1] = 0.0;
	}
	else if (discriminant < 0.0)
	{
		//zwracamy warto�� null kiedy nie wyst�puje przeci�cie ze sfer�
		return nullptr;
	}

	return u;
}
