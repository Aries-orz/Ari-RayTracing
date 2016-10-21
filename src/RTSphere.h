#pragma once

#include "RTObject.h"
#include "Vec3d.h"

namespace rt {

class RTSphere : public RTObject {
public:
	Vec3d pos;
	double rad;

	RTSphere(Vec3d p, Vec3d e, Vec3d c, double r, Material m);

	double hit(const Ray& r);
    Vec3d getNormal(const Ray& r, const double t) const;
};

}