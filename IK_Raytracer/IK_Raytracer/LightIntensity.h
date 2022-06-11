#pragma once
#include <ostream>
#include <vector>
#include "Hitable.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"

#define LEFT_UPPER 0
#define RIGHT_UPPER 1
#define RIGHT_LOWER 2
#define LEFT_LOWER 3
#define CENTER 4

class LightIntensity
{
protected:
	double r, g, b = 0.0f;
	float maxSteps = 0.125f;
public:
	LightIntensity(double R, double G, double B) { r = R; g = G; b = B; }
	LightIntensity(double R, double G) { r = R; g = G; b = 0.0f; }
	LightIntensity(double R) { r = R; g = b = 0.0f; }
	LightIntensity() { r = g = b = 0.0; }

	double getRed() { return r; }
	double getGreen() { return g; }
	double getBlue() { return b; }

	void operator()(float R, float G, float B) { r = R; g = G; b = B; }
	void operator()(float R, float G) { r = R; g = G; b = 0.0f; }
	void operator()(float R) { r = R; g = b = 0.0f; }

	void add(double R, double G, double B);

	LightIntensity operator+(LightIntensity& li);
	LightIntensity operator+(LightIntensity li);
	LightIntensity operator-(LightIntensity& li);
	LightIntensity operator*(float num);
	LightIntensity operator*(vec3 v);
	LightIntensity operator+(vec3 v);
	LightIntensity operator/(float num);

	void operator+=(LightIntensity li);
	void operator-=(LightIntensity& li);
	void operator*=(float num);
	void operator/=(float num);

	bool operator==(const LightIntensity& li);

	LightIntensity multiply(LightIntensity li, vec3 color);

	friend LightIntensity operator*(float num, LightIntensity& li);

	LightIntensity Antialiasing(Hitable* world, Camera* camera, float fov, float m, bool ortho, float xMin, float xMax, float yMin, float yMax, int x, int y, float w, std::vector<LightIntensity*> colors, std::vector<PointLight> pointLights, std::vector<DirectionalLight> directionalLights);

	LightIntensity GetColorFromRay(const Ray& r, Hitable* world, vec3 cameraPosition, std::vector<PointLight> pointLights, std::vector<DirectionalLight> directionalLights, int bounce);

	// Methods to ensure that color is in range of [0-255]
	float red(float redValue);
	float green(float greenValue);
	float blue(float blueValue);
};

