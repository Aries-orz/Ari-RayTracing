#include "RTBox.h"

namespace rt {
    
RTBox::RTBox(Vec3d _p0, Vec3d _p1, Material m, Vec3d e, Vec3d c)
: p0(_p0), p1(_p1), RTObject(m,e,c), face(-1) {}
    
double RTBox::hit(const Ray& r) {
    double tmin = 0;
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
    int face_in, face_out;
    if (tx_min > ty_min) {
        t0 = tx_min;
        face_in = (a >= 0.0) ? 0 : 3;
    } else {
        t0 = ty_min;
        face_in = (b >= 0.0) ? 1 : 4;
    }
    if (tz_min > t0) {
        t0 = tz_min;
        face_in = (c >= 0.0) ? 2 : 5;
    }
        
    if (tx_max < ty_max) {
        t1 = tx_max;
        face_out = (a >= 0.0) ? 3 : 0;
    } else {
        t1 = ty_max;
        face_out = (b >= 0.0) ? 4 : 1;
    }
    if (tz_max < t1) {
        t1 = tz_max;
        face_out = (c >= 0.0) ? 5 : 2;
    }
        
    if (t0 < t1 && t1 > 1e-4) {
        if (t0 > 1e-4) {
            tmin = t0;
            face = face_in;
        } else {
            tmin = t1;
            face = face_out;
        }
    }
    return tmin;
}
    
Vec3d RTBox::getNormal(const Ray& r, const double t) const {
    switch (face) {
        case 0: return Vec3d(-1,0,0);
        case 1: return Vec3d(0,-1,0);
        case 2: return Vec3d(0,0,-1);
        case 3: return Vec3d(1,0,0);
        case 4: return Vec3d(0,1,0);
        case 5: return Vec3d(0,0,1);
    }
    return Vec3d();
}
    
}
