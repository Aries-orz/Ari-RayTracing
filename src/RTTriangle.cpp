#include "RTTriangle.h"

namespace rt {

RTTriangle::RTTriangle() {}
    
RTTriangle::RTTriangle(Vec3d _p0, Vec3d _p1, Vec3d _p2, Material m, Vec3d e, Vec3d c)
: p0(_p0), p1(_p1), p2(_p2), RTObject(m,e,c) {}

double RTTriangle::hit(const Ray& r) {
	Vec3d e1 = p1 - p0;
	Vec3d e2 = p2 - p0;
	Vec3d p = (r.d)^(e2);
	double det = e1.dot(p);
	Vec3d tt;
	if (det > 0) tt = r.o - p0;
	else {
		tt = p0 - r.o;
		det = -det;
	}
	if (det < 0.0001f) return 0;
	double u = tt.dot(p);
	if (u < 0.0f || u > det) return 0;
	Vec3d q = tt^e1;
	double v = r.d.dot(q);
	if (v < 0.0f || u+v > det) return 0;
	if (e2.dot(q) <= 0) return 0;
	double t = e2.dot(q);
	double invDet = 1.0f / det;
	t *= invDet;
	return t;
}
    
Vec3d RTTriangle::getNormal(const Ray& r, const double t) const {
    double a = (p1.y-p0.y) * (p2.z-p0.z) - (p1.z-p0.z) * (p2.y-p0.y);
    double b = (p1.z-p0.z) * (p2.x-p0.x) - (p1.x-p0.x) * (p2.z-p0.z);
    double c = (p1.x-p0.x) * (p2.y-p0.y) - (p1.y-p0.y) * (p2.x-p0.x);
    Vec3d n(a,b,c);
    n.norm();
    return n.dot(r.d) < 0 ? n : n*-1;
}

}