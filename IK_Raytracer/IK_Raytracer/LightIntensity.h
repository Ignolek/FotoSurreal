#pragma once
#include <ostream>
#include <vector>
#include "Hitable.h"
#include "Camera.h"

#define LEFT_UPPER 0
#define RIGHT_UPPER 1
#define RIGHT_LOWER 2
#define LEFT_LOWER 3
#define CENTER 4

class LightIntensity
{
protected:
	double r, g, b;
	float maxSteps = 4;
public:
	LightIntensity(double R, double G, double B) { r = R; g = G; b = B; }
	LightIntensity(double R, double G) { r = R; g = G; b = 0.0; }
	LightIntensity(double R) { r = R; g = b = 0.0; }
	LightIntensity() { r = g = b = 0.0; }

	double getRed() { return r; }
	double getGreen() { return g; }
	double getBlue() { return b; }

	void operator()(float R, float G, float B) { r = R; g = G; b = B; }
	void operator()(float R, float G) { r = R; g = G; b = 0.0; }
	void operator()(float R) { r = R; g = b = 0.0; }

	void add(double R, double G, double B);

	LightIntensity operator+(LightIntensity& li);
	LightIntensity operator+(LightIntensity li);
	LightIntensity operator-(LightIntensity& li);
	LightIntensity operator*(float num);
	LightIntensity operator/(float num);

	//LightIntensity operator+=(LightIntensity& li);
	LightIntensity operator+=(LightIntensity li);
	void operator-=(LightIntensity& li);
	void operator*=(float num);
	void operator/=(float num);

	bool operator==(LightIntensity& li);

	friend LightIntensity operator*(float num, LightIntensity& li);
	friend LightIntensity operator*(LightIntensity& li, float num);

	LightIntensity Antialiasing(Hitable* world, Camera* camera, float fov, float m, bool ortho, float xMin, float xMax, float yMin, float yMax, int x, int y, float w, std::vector<LightIntensity*> colors);

	LightIntensity GetColorFromRay(const Ray& r, Hitable* world);

	//friend std::ostream& operator<<(std::ostream& str, LightIntensity& li);
};

