#include "RTBBox.h"

namespace rt {
    
RTBBox::RTBBox(Vec3d _p0, Vec3d _p1):p0(_p0), p1(_p1) {}

double RTBBox::hit(const Ray& r) {
    double ox = r.o.x, oy = r.o.y, oz = r.o.z;
    double dx = r.d.x, dy = r.d.y, dz = r.d.z;
    double x0 = p0.x, y0 = p0.y, z0 = p0.z;
    double x1 = p1.x, y1 = p1.y, z1 = p1.z;
    
    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;
    
    double a = 1.0/dx;
    if (a >= 0) {
        tx_min = (x0 - ox) * a;
        tx_max = (x1 - ox) * a;
    } else {
        tx_min = (x1 - ox) * a;
        tx_max = (x0 - ox) * a;
    }
    
    double b = 1.0/dy;
    if (b >= 0) {
        ty_min = (y0 - oy) * b;
        ty_max = (y1 - oy) * b;
    } else {
        ty_min = (y1 - oy) * b;
        ty_max = (y0 - oy) * b;
    }
    
    double c = 1.0/dz;
    if (c >= 0) {
        tz_min = (z0 - oz) * c;
        tz_max = (z1 - oz) * c;
    } else {
        tz_min = (z1 - oz) * c;
        tz_max = (z0 - oz) * c;
    }
    
    double t0, t1;
    if (tx_min > ty_min)
        t0 = tx_min;
    else
        t0 = ty_min;
    if (tz_min > t0)
        t0 = tz_min;
    
    if (tx_max < ty_max)
        t1 = tx_max;
    else
        t1 = ty_max;
    if (tz_max < t1)
        t1 = tz_max;
    
    if (t0 < t1 && t1 > 1e-4) return 1;
    return 0;
}

Vec3d RTBBox::getNormal(const Ray& r, const double t) const { return Vec3d(); }
    
}
