#pragma once

#include "Vec3d.h"

namespace rt {

class Ray {
public:
	Vec3d o, d;

	Ray();
	Ray(Vec3d _o, Vec3d _d);
};

}