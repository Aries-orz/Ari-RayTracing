#pragma once

#include "RTObject.h"
#include "RTTriangle.h"
#include "RTBBox.h"
#include <vector>

namespace rt {
    
class RTComplexObj : public RTObject {
public:
    RTTriangle* indices;
    RTBBox* bbox;
    
    RTComplexObj(RTTriangle* v, RTBBox* b, int s, Material m, Vec3d e, Vec3d c);
    ~RTComplexObj();
    
    double hit(const Ray& r);
    Vec3d getNormal(const Ray& r, const double t) const;
    
protected:
    int index;
    int size;
};
    
}
