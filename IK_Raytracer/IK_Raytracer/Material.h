#pragma once
#include "Hitable.h"
#include <random>
class Material
{
public:
	virtual bool scatter(const Ray& r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered) const = 0;

	vec3 randomInUnitSphere() const
	{
		vec3 p;
		do
		{
			p = 2.0 * vec3(randomFloat(), randomFloat(), randomFloat()) - vec3(1, 1, 1);
		} while (p.squared_length() >= 1.0f);

		return p;
	}

	double randomFloat() const
	{
		double result;
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_real_distribution<> distr(0, 2);

		result = distr(eng) / 2.0f;
		return result;
	}
};

