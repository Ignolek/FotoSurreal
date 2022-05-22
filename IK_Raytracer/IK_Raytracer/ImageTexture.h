#pragma once
#include "vec3.h"
class ImageTexture
{
public:
	unsigned char* data;
	int nX, nY;

	ImageTexture(){}
	ImageTexture(unsigned char* pixels, int A, int B);
	vec3 value(float u, float v, vec3& p) const;
};

