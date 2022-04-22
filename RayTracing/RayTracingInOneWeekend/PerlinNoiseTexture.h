#pragma once
#include "Texture.h"
#include "PerlinNoise.h"
class PerlinNoiseTexture :public Texture
{
public:
    PerlinNoiseTexture()
    {

    }
    virtual Color Value(double u, double v, const Point3& p) const override
    {
        return Color(1, 1, 1) * perlinNoise.Noise(p);
    }
public:
    PerlinNoise perlinNoise;
};

