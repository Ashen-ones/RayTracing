#pragma once
#include "Texture.h"
class CheckerTexture :public Texture
{
public:
	CheckerTexture() {}

	CheckerTexture(shared_ptr<Texture> _even, shared_ptr<Texture> _odd)
		: even(_even), odd(_odd) {}

	CheckerTexture(Color c1, Color c2)
		: even(make_shared<SolidColor>(c1)), odd(make_shared<SolidColor>(c2)) {}

	virtual Color Value(double u, double v, const Point3& p) const override {
		auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
		if (sines < 0)
			return odd->Value(u, v, p);
		else
			return even->Value(u, v, p);
	}

public:
	shared_ptr<Texture> odd;
	shared_ptr<Texture> even;
};

