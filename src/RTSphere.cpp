#include "RTSphere.h"
#include <cmath>

namespace rt {

RTSphere::RTSphere(Vec3d p, Vec3d e, Vec3d c, double r, Material m)
: pos(p), rad(r), RTObject(m,e,c) {}

double RTSphere::hit(const Ray& r) {
	Vec3d dis = pos - r.o;
	double t;
	double eps = 1e-4;
	double b = dis.dot(r.d);
	double det = b*b - dis.dot(dis) + rad*rad;
	if (det < 0) return 0;
	else det = sqrt(det);

    return (t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0);
}
    
Vec3d RTSphere::getNormal(const Ray& r, const double t) const {
    Vec3d x = r.o + r.d*t;
    return (x-pos).norm();
}

}