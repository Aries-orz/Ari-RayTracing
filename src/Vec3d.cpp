#include "Vec3d.h"
#include <math.h>

namespace rt {

Vec3d::Vec3d(const Vec3d& v):x(v.x), y(v.y), z(v.z) {}

Vec3d Vec3d::operator +(const Vec3d& v) const {
	return Vec3d(x+v.x, y+v.y, z+v.z);
}

Vec3d Vec3d::operator -(const Vec3d& v) const {
	return Vec3d(x-v.x, y-v.y, z-v.z);
}

Vec3d Vec3d::operator *(const Vec3d& v) const {
	return Vec3d(x*v.x, y*v.y, z*v.z);
}

Vec3d Vec3d::operator *(double d) const {
	return Vec3d(x*d, y*d, z*d);
}

Vec3d Vec3d::operator ^(const Vec3d& v) const {
	return Vec3d(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}

Vec3d& Vec3d::operator =(const Vec3d& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vec3d& Vec3d::norm() {
	return *this = (*this) * (1/sqrt(x*x+y*y+z*z));
}

double Vec3d::dot(const Vec3d& v) const {
	return x*v.x + y*v.y + z*v.z;
}

}