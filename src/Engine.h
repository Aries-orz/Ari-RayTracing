#pragma once

#include "Vec3d.h"
#include "Ray.h"
#include "Scene.h"
#include <cstdlib>
#include <cmath>

namespace rt {

namespace engine {

    //Compute the radiance
    extern Vec3d radianceRT(const Ray &r, int depth, Scene* scene);
    //Sampling based on ray tracing
    extern void raytracing(Scene* scene, int samps, Ray camera, int w, int h, const char* outfile);
    
    //Control the RGB value in the range [0,255]
    inline double clamp(double x) {
        return x<0 ? 0 : x>1 ? 1 : x;
    }
    
    //A pseudo-random number generator
    inline double randRT() {
        return (double)rand() / (double)RAND_MAX;
    }
    
    //Make a gamma correction of 2.2
    inline int toInt(double x) {
        return int(pow(clamp(x), 1/2.2) * 255 + .5);
    }
    
}
    
}
