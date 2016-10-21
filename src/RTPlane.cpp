#include "RTPlane.h"

namespace rt {
    
RTPlane::RTPlane(const Vec3d& p, const Vec3d& n, Material m, Vec3d e, Vec3d c)
: point(p), normal(n), rt::RTObject(m,e,c) {}
   
double RTPlane::hit(const Ray& r) {
    double t = (point - r.o).dot(normal) / (r.d).dot(normal);
    if (t > 1e-4)
        return t;
    else
        return 0;
}
    
Vec3d RTPlane::getNormal(const Ray& r, const double t) const {
    return normal.dot(r.d) < 0 ? normal : normal*-1;
}
    
}
