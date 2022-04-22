#pragma once
#include "Material.h"
#include "Texture.h"

class DiffuseLight :
    public Material
{
public:
    DiffuseLight(shared_ptr<Texture> a) : emit(a) {}
    DiffuseLight(Color c) :emit(make_shared<SolidColor>(c)) {}

    virtual bool Scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        return false;
    }
    virtual Color Emitted(double u, double v, const Point3& p)const override {
        return emit->Value(u, v, p);
    }
public:
    shared_ptr<Texture> emit;
};

