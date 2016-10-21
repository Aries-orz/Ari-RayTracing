#pragma once

#include "Vec3d.h"
#include "RTObject.h"

namespace rt {

class RTBox : public RTObject {
public:
    Vec3d p0, p1;
    
    RTBox(Vec3d _p0, Vec3d _p1, Material m, Vec3d e, Vec3d c);
    
    double hit(const Ray& r);
    Vec3d getNormal(const Ray& r, const double t) const;
    
protected:
    int face;
    
};
    
}
