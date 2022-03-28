#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include "Libraries/stb_image.h"
#include "Libraries/stb_image_write.h"

Image::Image(const char* filename) {
	if (Read(filename)) {
		std::cout << "Read " << filename << std::endl;
		size = w * h * channels;
	}
	else
	{
		std::cout << "Failed to read " << filename << std::endl;
	}
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
	size = w * h * channels;
	data = new uint8_t[size];
}
Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
	memcpy(data, img.data, size);
}
Image::~Image() {
	stbi_image_free(data);
}

bool Image::Read(const char* filename) {
	data = stbi_load(filename, &w, &h, &channels, 0);
	return data != NULL;
}
bool Image::Write(const char* filename) {
	ImageType type = GetFileType(filename);
	int success;
	switch (type)
	{
	case PNG:
		success = stbi_write_png(filename, w, h, channels, data, w * channels);
		break;
	case JPG:
		success = stbi_write_jpg(filename, w, h, channels, data, 100);
		break;
	case BMP:
		success = stbi_write_bmp(filename, w, h, channels, data);
		break;
	case TGA:
		success = stbi_write_tga(filename, w, h, channels, data);
		break;
	default:
		break;
	}
	return success != 0;
}

ImageType Image::GetFileType(const char* filename)
{
	const char* ext = strrchr(filename, '.');
	if (ext != nullptr) {
		if (strcmp(ext, ".png") == 0)
		{
			return PNG;
		}
		else if (strcmp(ext, ".jpg") == 0)
		{
			return JPG;
		}
		else if (strcmp(ext, ".bmp") == 0)
		{
			return BMP;
		}
		else if (strcmp(ext, ".tga") == 0)
		{
			return TGA;
		}
	}
	return PNG;
}

Image& Image::FillColor(float r, float g, float b)
{
	if (channels < 3) {
		std::cout << "Not enough channels" << std::endl;
	}
	else {
		for (int i = 0; i < size; i += channels) {
			data[i] *= r / 255;
			data[i + 1] *= g / 255;
			data[i + 2] *= b / 255;
		}
	}
	return *this;
}

Image& Image::FillColor(LightIntensity color)
{
	if (channels < 3) {
		std::cout << "Not enough channels" << std::endl;
	}
	else {
		for (int i = 0; i < size; i += channels) {
			data[i] *= color.getRed() / 255;
			data[i + 1] *= color.getGreen() / 255;
			data[i + 2] *= color.getBlue() / 255;
		}
	}
	return *this;
}

void Image::SetPixel(int x, int y, LightIntensity color)
{
	uint8_t* buf_data = this->data;

	buf_data[this->channels * (y * this->w + x) + 0] = color.getRed();
	buf_data[this->channels * (y * this->w + x) + 1] = color.getGreen();
	buf_data[this->channels * (y * this->w + x) + 2] = color.getBlue();

	this->data = buf_data;
}

//void Image::DrawTriangle(Vector p1, Vector p2, Vector p3, LightIntensity color)
//{
//	for (int xi = 0; xi < w; xi++) {
//		for (int yi = 0; yi < h; yi++)
//		{
//			if (xi > minx && xi < maxx && yi > miny && yi < maxy)
//			{
//				if ((((p1.x - p2.x) * (yi - p1.y) - (p1.y - p2.y) * (xi - p1.x)) > 0) &&
//					(((p2.x - p3.x) * (yi - p2.y) - (p2.y - p3.y) * (xi - p2.x)) > 0) &&
//					(((p3.x - p1.x) * (yi - p3.y) - (p3.y - p1.y) * (xi - p3.x)) > 0))
//				{
//					if (tl3 == true && tl2 == true)
//					{
//						this->SetPixel(xi, yi, color);
//					}
//				}
//			}
//		}
//	}
//}
