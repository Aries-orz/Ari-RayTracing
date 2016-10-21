#pragma once

#include "Vec3d.h"
#include "Ray.h"
#include "Scene.h"
#include <stdlib.h>

namespace rt {

class Engine {
public:
    static Vec3d radianceRT(const Ray &r, int depth, Scene& scene);
    
    static double randRT() {
        return (double)rand() / (double)RAND_MAX;
    }
};
    
}
