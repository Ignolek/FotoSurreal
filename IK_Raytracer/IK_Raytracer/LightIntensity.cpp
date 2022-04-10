#include "LightIntensity.h"
#include "Ray.h"

void LightIntensity::add(double R, double G, double B)
{
	this->r += R;
	this->g += G;
	this->b += B;
}

LightIntensity LightIntensity::operator+(LightIntensity& li)
{
	LightIntensity Result;
	Result.r = (this->r + li.r);
	Result.g = (this->g + li.g);
	Result.b = (this->b + li.b);
	return Result;
}

LightIntensity LightIntensity::operator+(LightIntensity li)
{
	LightIntensity Result;
	Result.r = (this->r + li.r);
	Result.g = (this->g + li.g);
	Result.b = (this->b + li.b);
	return Result;
}

LightIntensity LightIntensity::operator-(LightIntensity& li)
{
	LightIntensity Result;
	Result.r = (this->r - li.r);
	Result.g = (this->g - li.g);
	Result.b = (this->b - li.b);
	return Result;
}

LightIntensity LightIntensity::operator*(float num)
{
	LightIntensity Result;
	Result.r = (this->r * num);
	Result.g = (this->g * num);
	Result.b = (this->b * num);
	return Result;
}

LightIntensity LightIntensity::operator/(float num)
{
	LightIntensity Result;
	Result.r = (this->r / num);
	Result.g = (this->g / num);
	Result.b = (this->b / num);
	return Result;
}

//LightIntensity LightIntensity::operator+=(LightIntensity& li)
//{
//	LightIntensity Result;
//	Result.r = this->r + li.r;
//	Result.g = this->g + li.g;
//	Result.b = this->b + li.b;
//	return Result;
//}

void LightIntensity::operator+=(LightIntensity li)
{
	this->r = this->r + li.r;
	this->g = this->g + li.g;
	this->b = this->b + li.b;
}

void LightIntensity::operator-=(LightIntensity& li)
{
	this->r = this->r - li.r;
	this->g = this->g - li.g;
	this->b = this->b - li.b;
}

void LightIntensity::operator*=(float num)
{
	this->r = this->r * num;
	this->g = this->g * num;
	this->b = this->b * num;
}

void LightIntensity::operator/=(float num)
{
	this->r = this->r / num;
	this->g = this->g / num;
	this->b = this->b / num;
}

bool LightIntensity::operator==(const LightIntensity& li)
{
	if (this->r == li.r && this->g == li.g && this->b == li.b)
		return true;
	else return false;
}



LightIntensity LightIntensity::Antialiasing(Hitable* world, Camera* camera, float fov, float m, bool ortho, float xMin, float xMax, float yMin, float yMax, int x, int y, float w, std::vector<LightIntensity*> colors)
{
	LightIntensity result(0.0f);
	Ray ray;

	if (colors[LEFT_UPPER] == nullptr)
	{
		ray = camera->getRay(xMin, yMin, fov, m, ortho);
		colors[LEFT_UPPER] = new LightIntensity(this->GetColorFromRay(ray,world));
	}
	if (colors[RIGHT_UPPER] == nullptr)
	{
		ray = camera->getRay(xMax, yMin, fov, m, ortho);
		colors[RIGHT_UPPER] = new LightIntensity(this->GetColorFromRay(ray, world));
	}
	if (colors[RIGHT_LOWER] == nullptr)
	{
		ray = camera->getRay(xMax, yMax, fov, m, ortho);
		colors[RIGHT_LOWER] = new LightIntensity(this->GetColorFromRay(ray, world));
	}
	if (colors[LEFT_LOWER] == nullptr)
	{
		ray = camera->getRay(xMin, yMax, fov, m, ortho);
		colors[LEFT_LOWER] = new LightIntensity(this->GetColorFromRay(ray, world));
	}
	if (colors[CENTER] == nullptr)
	{
		ray = camera->getRay((xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f, fov, m, ortho);
		colors[CENTER] = new LightIntensity(this->GetColorFromRay(ray, world));
	}

	if (w < maxSteps || *colors[LEFT_UPPER] == *colors[CENTER])
	{
		result += *colors[LEFT_UPPER];
	}
	else 
	{
		result += Antialiasing(world, camera, fov, m, ortho, xMin, (xMin + xMax) * 0.5f, yMin, (yMin + yMax) * 0.5f, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*colors[LEFT_UPPER]), nullptr, new LightIntensity(*colors[CENTER]), nullptr, nullptr});
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	if (w < maxSteps || *colors[RIGHT_UPPER] == *colors[CENTER])
	{
		result += *colors[RIGHT_UPPER];
	}
	else
	{
		result += Antialiasing(world, camera, fov, m, ortho, (xMin + xMax) * 0.5f, xMax , yMin, (yMin + yMax) * 0.5f, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*colors[RIGHT_UPPER]), nullptr, new LightIntensity(*colors[CENTER]), nullptr, nullptr});
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	if (w < maxSteps || *colors[RIGHT_LOWER] == *colors[CENTER])
	{
		result += *colors[RIGHT_LOWER];
	}
	else
	{
		result += Antialiasing(world, camera, fov, m, ortho, (xMin + xMax) * 0.5f, xMax, (yMin + yMax) * 0.5f, yMax, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*colors[CENTER]), nullptr, new LightIntensity(*colors[RIGHT_LOWER]), nullptr, nullptr});
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	if (w < maxSteps || *colors[LEFT_LOWER] == *colors[CENTER])
	{
		result += *colors[LEFT_LOWER];
	}
	else
	{
		result += Antialiasing(world, camera, fov, m, ortho, xMin, (xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f, yMax, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*colors[CENTER]), nullptr, new LightIntensity(*colors[LEFT_LOWER]), nullptr, nullptr});
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	for (int i = 0; i < 5; i++)
	{
		delete colors[i];
	}
	colors.clear();

	return 0.25f*result;
}

LightIntensity operator*(float num, LightIntensity& li)
{
	LightIntensity Result;
	Result.r = num * li.r;
	Result.g = num * li.g;
	Result.b = num * li.b;
	return Result;
}

//LightIntensity operator*(LightIntensity& li, float num)
//{
//	LightIntensity Result;
//	Result.r = li.r * num;
//	Result.g = li.g * num;
//	Result.b = li.b * num;
//	return Result;
//}

LightIntensity LightIntensity::GetColorFromRay(const Ray& r, Hitable* world)
{
	hitRecord rec;
	if (world->hit(r, 0.0, FLT_MAX, rec) == true)
	{
		return LightIntensity(255.99 * (rec.normal.x() + 1) * 0.5f, 255.99 * (rec.normal.y() + 1) * 0.5f, 255.99 * (rec.normal.z() + 1) * 0.5f);
	}
	else
	{
		vec3 unitDirection = unit_vector(r.direction());
		float t = 0.5 * (unitDirection.y() + 1.0);
		LightIntensity result = LightIntensity(1.0, 1.0, 1.0) * (1.0 - t) + LightIntensity(0.5, 0.7, 1.0) * t;
		return LightIntensity(result.getRed() * 255.99, result.getGreen() * 255.99, result.getBlue() * 255.99);
	}
}