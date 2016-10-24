#pragma once

#include "Vec3d.h"

namespace rt {

class Ray {
public:
    //the origin and direction of the ray
	Vec3d o, d;

	Ray();
	Ray(Vec3d _o, Vec3d _d);
};

}