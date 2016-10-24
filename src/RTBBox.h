#pragma once

#include "Vec3d.h"
#include "Ray.h"
#include "RTObject.h"

namespace  rt {

class RTBBox : public RTObject {
public:
    Vec3d p0, p1;
    
    RTBBox(Vec3d _p0, Vec3d _p1);
    
    double hit(const Ray& r );
    Vec3d getNormal(const Ray& r, const double t) const;
        
};
    
}
