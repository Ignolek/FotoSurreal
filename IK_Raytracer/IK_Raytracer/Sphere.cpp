#include "Sphere.h"

Sphere::Sphere() : coords(0,0,0), radius(0) {}

Sphere::Sphere(Vector coordinates, float r)
{
	this->coords = coordinates;
	this->radius = r;
}

Vector* Sphere::intersect(Ray& ray)
{
	//obliczamy równanie kwadratowe
	Vector v = ray.getOrigin() - this->coords;
	float a = ray.getDirection().dotProduct(ray.getDirection());
	float b = 2.0 * v.dotProduct(ray.getDirection());
	float c = v.dotProduct(v) - (this->radius * this->radius);
	float u[2];

	Vector* crossCoord = nullptr;
	//obliczamy wyró¿nik kwadratowy
	float discriminant = b * b - 4 * a * c;
	//zwracamy lokacje przeciêcia
	if (discriminant > 0.0)
	{
		const float root = sqrt(discriminant);
		const float denom = 2.0 * a;

		crossCoord = new Vector(((-b + root) / denom), ((-b - root) / denom), 0);
		/*u[0] = (-b + root) / denom;
		u[1] = (-b - root) / denom;*/
	}
	else if (discriminant == 0.0)
	{
		const float denom = 2.0 * a;

		crossCoord = new Vector(((-b) / denom), 0.0, 0.0);
		/*u[0] = (-b) / denom;
		u[1] = 0.0;*/
	}
	else if (discriminant < 0.0)
	{
		//zwracamy wartoœæ null kiedy nie wystêpuje przeciêcie ze sfer¹
		return nullptr;
	}

	return crossCoord;
}
