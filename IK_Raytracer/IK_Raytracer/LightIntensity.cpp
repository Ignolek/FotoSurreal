#include "LightIntensity.h"

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

void LightIntensity::operator+=(LightIntensity& li)
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

LightIntensity operator*(float num, LightIntensity& li)
{
	LightIntensity Result;
	Result.r = num * li.r;
	Result.g = num * li.g;
	Result.b = num * li.b;
	return Result;
}

LightIntensity operator*(LightIntensity& li, float num)
{
	LightIntensity Result;
	Result.r = li.r * num;
	Result.g = li.g * num;
	Result.b = li.b * num;
	return Result;
}
