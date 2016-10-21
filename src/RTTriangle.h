#pragma once

#include "RTObject.h"
#include "Vec3d.h"

namespace rt {

class RTTriangle : public RTObject {
public:
	Vec3d p0, p1, p2;
    RTTriangle();
	RTTriangle(Vec3d _p0, Vec3d _p1, Vec3d _p2, Material m, Vec3d e, Vec3d c);

	double hit(const Ray& r);
    Vec3d getNormal(const Ray& r, const double t) const;
};

}