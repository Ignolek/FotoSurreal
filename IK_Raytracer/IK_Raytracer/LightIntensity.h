#pragma once
#include <ostream>

class LightIntensity
{
protected:
	double r, g, b;
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
	LightIntensity operator-(LightIntensity& li);
	LightIntensity operator*(float num);
	LightIntensity operator/(float num);

	void operator+=(LightIntensity& li);
	void operator-=(LightIntensity& li);
	void operator*=(float num);
	void operator/=(float num);

	friend LightIntensity operator*(float num, LightIntensity& li);
	friend LightIntensity operator*(LightIntensity& li, float num);

	//friend std::ostream& operator<<(std::ostream& str, LightIntensity& li);
};

