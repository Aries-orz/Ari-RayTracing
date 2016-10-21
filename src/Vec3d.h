#pragma once

namespace rt {

class Vec3d {
public:
	double x, y, z;

	Vec3d(double _x = 0, double _y = 0, double _z = 0):x(_x), y(_y), z(_z) {}
	Vec3d(const Vec3d& v);
	// virtual ~Vec3d();

	Vec3d operator +(const Vec3d& v) const;
	Vec3d operator -(const Vec3d& v) const;
	Vec3d operator *(const Vec3d& v) const;
	Vec3d operator *(double d) const;
	Vec3d operator ^(const Vec3d& v) const;
	Vec3d& operator =(const Vec3d& v);
	Vec3d& norm();
	double dot(const Vec3d& v) const;
};

}