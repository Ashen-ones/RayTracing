#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
class ImageTexture :
    public Texture
{
public :
    const static int bytesPerPixel = 3;
    ImageTexture() :data(nullptr), width(0), height(0), bytesPerScanline(0) {}

    ~ImageTexture()
    {
        delete[] data;
    }

	ImageTexture(const char* filename)
	{
		auto compontensPerPixel = bytesPerPixel;

		data = stbi_load(filename, &width, &height, &compontensPerPixel, compontensPerPixel);

		if (!data)
		{
			std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
			width = height = 0;
		}

		bytesPerScanline = compontensPerPixel * width;
	}

    virtual Color Value(double u, double v, const Vec3& p) const override {
        if (!data)
        {
            return  Color(0, 1, 1);
        }

        u = clamp(u, 0.0, 1.0);
        v = 1.0 - clamp(v, 0.0, 1.0);

		auto i = static_cast<int>(u * width);
		auto j = static_cast<int>(v * height);

		if (i >= width)  i = width - 1;
		if (j >= height) j = height - 1;

		const auto color_scale = 1.0/ 255.0;
		auto pixel = data + j * bytesPerScanline + i * bytesPerPixel;
		return Color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
    }

private:
	unsigned char* data;
    int width, height;
    int bytesPerScanline;
};

