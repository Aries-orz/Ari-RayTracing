#include "RTObject.h"

namespace rt {

RTObject::RTObject() {}
    
RTObject::RTObject(Material m, Vec3d e, Vec3d c):mat(m), emission(e), color(c) {}

RTObject::~RTObject() {}
    
}