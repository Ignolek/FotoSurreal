#include "ImageTexture.h"

ImageTexture::ImageTexture(unsigned char* pixels, int A, int B) : data(pixels), nX(A), nY(B){}

vec3 ImageTexture::value(float u, float v, vec3& p) const
{
	int i = ( u)*nX;
	int j = (1 - v) * nY - 0.001;
	if (i < 0) i = 0;
	if (j < 0) j = 0;
	if (i > nX - 1) i = nX - 1;
	if (j > nY - 1) j = nY - 1;

	float r = int(data[3 * i + 3 * nX * j])	;
	float g = int(data[3 * i + 3 * nX * j + 1]);
	float b = int(data[3 * i + 3 * nX * j + 2]);
	return vec3(r, g, b);
}
