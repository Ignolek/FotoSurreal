#pragma once

#include <cstdint>
#include <iostream>
#include "Vector.h"
#include "LightIntensity.h"
#include "vec3.h"

enum ImageType {
	PNG, JPG, BMP, TGA
};

class Image
{
private:
	uint8_t* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;
	float minx, miny, maxx, maxy;
	bool tl1, tl2, tl3 = false;
public:
	Image(const char* filename);
	Image(int w, int h, int channels);
	Image(const Image& img);

	~Image();

	bool Read(const char* filename);
	bool Write(const char* filename);

	ImageType GetFileType(const char* filename);

	Image& FillColor(float r, float g, float b);
	Image& FillColor(LightIntensity color);

	void SetPixel(int x, int y, LightIntensity color);
	//void DrawTriangle(Vector p1, Vector p2, Vector p3, LightIntensity color);
};