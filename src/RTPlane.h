#include "Vec3d.h"
#include "RTObject.h"

namespace rt {
    
class RTPlane : public RTObject{
public:
    RTPlane(const Vec3d& p, const Vec3d& n, Material m, Vec3d e, Vec3d c);
    
    double hit(const Ray& r);
    Vec3d getNormal(const Ray& r, const double t) const;
    
protected:
    Vec3d point;
    Vec3d normal;
};
    
}
