#include "RTComplexObj.h"

namespace rt {

RTComplexObj::RTComplexObj(RTTriangle* v, RTBBox* b, int s, Material m, Vec3d e, Vec3d c)
    : indices(v), bbox(b), index(0), size(s), RTObject(m,e,c) {}
    
RTComplexObj::~RTComplexObj() {
    delete [] indices;
    delete bbox;
}
    
double RTComplexObj::hit(const Ray& r) {
    if (!bbox->hit(r)) return 0;
    double tmin = 0;
    for (int i=0; i<size; ++i) {
        double t = indices[i].hit(r);
        if (!t) continue;
        if (t < tmin || !tmin) {
            tmin = t;
            index = i;
        }
    }
    return tmin;
}
    
Vec3d RTComplexObj::getNormal(const Ray& r, const double t) const {
    return indices[index].getNormal(r, t);
}

}
