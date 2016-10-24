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
    
    //Compute whether the ray will hit the object, and return the distance if yes or return 0 if no
	virtual double hit(const Ray& r) = 0;
    //Calculate the normal if the ray hits
    virtual Vec3d getNormal(const Ray& r, const double t) const = 0;
};

}