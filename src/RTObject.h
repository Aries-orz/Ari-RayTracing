#pragma once

#include "Vec3d.h"
#include "Ray.h"

namespace rt {

class RTObject {
public:
	enum Material { DIFFUSE, SPECULAR, REFRACTIVE };
	Material mat;
	Vec3d emission, color;

    RTObject();
	RTObject(Material m, Vec3d e, Vec3d c);
    virtual ~RTObject();
    
	virtual double hit(const Ray& r) = 0;
    virtual Vec3d getNormal(const Ray& r, const double t) const = 0;
};

}