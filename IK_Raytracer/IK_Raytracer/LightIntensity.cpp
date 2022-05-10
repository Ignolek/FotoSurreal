#include "LightIntensity.h"
#include "DirectionalLight.h"
#include "PointLight.h"
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
	maxSteps = 0.125f;
	LightIntensity result(0.0f, 0.0f, 0.0f);
	Ray ray(vec3(0,0,0), vec3(0,0,1));

	if (colors[LEFT_UPPER] == nullptr)
	{
		ray = camera->getRay(xMin, yMin, fov, m, ortho);
		colors[LEFT_UPPER] = new LightIntensity(this->GetColorFromRay(ray,world, 0));
	}
	if (colors[RIGHT_UPPER] == nullptr)
	{
		ray = camera->getRay(xMax, yMin, fov, m, ortho);
		colors[RIGHT_UPPER] = new LightIntensity(this->GetColorFromRay(ray, world, 0));
	}
	if (colors[RIGHT_LOWER] == nullptr)
	{
		ray = camera->getRay(xMax, yMax, fov, m, ortho);
		colors[RIGHT_LOWER] = new LightIntensity(this->GetColorFromRay(ray, world, 0));
	}
	if (colors[LEFT_LOWER] == nullptr)
	{
		ray = camera->getRay(xMin, yMax, fov, m, ortho);
		colors[LEFT_LOWER] = new LightIntensity(this->GetColorFromRay(ray, world, 0));
	}
	if (colors[CENTER] == nullptr)
	{
		ray = camera->getRay((xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f, fov, m, ortho);
		colors[CENTER] = new LightIntensity(this->GetColorFromRay(ray, world, 0));
	}

	if (w < maxSteps || *colors[LEFT_UPPER] == *colors[CENTER])
	{
		result += *colors[LEFT_UPPER];
	}
	else 
	{
		result += this->Antialiasing(world, camera, fov, m, ortho, xMin, (xMin + xMax) * 0.5f, yMin, (yMin + yMax) * 0.5f, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*colors[LEFT_UPPER]), nullptr, new LightIntensity(*colors[CENTER]), nullptr, nullptr});
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	if (w < maxSteps || *colors[RIGHT_UPPER] == *colors[CENTER])
	{
		result += *colors[RIGHT_UPPER];
	}
	else
	{
		result += this->Antialiasing(world, camera, fov, m, ortho, (xMin + xMax) * 0.5f, xMax , yMin, (yMin + yMax) * 0.5f, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*colors[RIGHT_UPPER]), nullptr, new LightIntensity(*colors[CENTER]), nullptr, nullptr});
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	if (w < maxSteps || *colors[RIGHT_LOWER] == *colors[CENTER])
	{
		result += *colors[RIGHT_LOWER];
	}
	else
	{
		result += this->Antialiasing(world, camera, fov, m, ortho, (xMin + xMax) * 0.5f, xMax, (yMin + yMax) * 0.5f, yMax, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*colors[CENTER]), nullptr, new LightIntensity(*colors[RIGHT_LOWER]), nullptr, nullptr});
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	if (w < maxSteps || *colors[LEFT_LOWER] == *colors[CENTER])
	{
		result += *colors[LEFT_LOWER];
	}
	else
	{
		result += this->Antialiasing(world, camera, fov, m, ortho, xMin, (xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f, yMax, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*colors[CENTER]), nullptr, new LightIntensity(*colors[LEFT_LOWER]), nullptr, nullptr});
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

LightIntensity LightIntensity::GetColorFromRay(const Ray& r, Hitable* world, int bounce)
{
	hitRecord rec;
	DirectionalLight dirLight(vec3(1.0, 0.9, 0.7), vec3(3, -1, -1));
	if (world->hit(r, 0.0, 100, rec))
	{
		vec3 color = dirLight.getDiffuse(rec);
	
		return LightIntensity(rec.materialPtr->mDiffuse.r() * color.r(), rec.materialPtr->mDiffuse.g() * color.g(), rec.materialPtr->mDiffuse.b() * color.b());
	}
	else
	{
		return LightIntensity(dirLight.color.r() * 255.0f, dirLight.color.g() * 255.0f, dirLight.color.b() * 255.0f);
	}
}