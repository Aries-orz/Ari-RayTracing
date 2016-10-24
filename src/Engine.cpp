#include "Engine.h"
#include <cstdio>

namespace rt {
    
namespace engine {

Vec3d radianceRT(const Ray &r, int depth, Scene* scene) {
    double tmin = 0;
    int id = 0;
    int objSize = scene->getSize();
    for (int i=0; i<objSize; ++i) {
        double t = scene->getObj(i)->hit(r);
        if (!t) continue;
        if (t < tmin || !tmin) {
            tmin = t;
            id = i;
        }
    }
    if (!tmin) return Vec3d();
        
    Vec3d x = r.o + r.d * tmin;
    RTObject *obj = scene->getObj(id);
    Vec3d n = obj->getNormal(r, tmin);
    Vec3d nl = n.dot(r.d)<0 ? n : n*-1;
    Vec3d f = obj->color;
    double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z;
        
    if (depth > 100) return obj->emission;
    if (++depth > 5) {
        if (randRT() < p) f = f * (1/p);
        else return obj->emission;
    }
    //Diffuse reflection
    if (obj->mat == RTObject::DIFFUSE) {
            double r1 = 2 * M_PI * randRT();
            double r2 = randRT(), r2s = sqrt(r2);
            Vec3d w = nl, u = ((fabs(w.x)>.1 ? Vec3d(0,1,0) : Vec3d(1,0,0))^w).norm(), v = w^u;
            Vec3d d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
            return obj->emission + f * (radianceRT(Ray(x,d), depth, scene));
        }
    //Specular reflection
    else if (obj->mat == RTObject::SPECULAR)
        return obj->emission + f * (radianceRT(Ray(x, r.d-n*2*n.dot(r.d)), depth, scene));
    //Refraction
    Ray reflRay(x, r.d-n*2*n.dot(r.d));
    bool into = n.dot(nl)>0;
    double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.d.dot(nl), cos2t;
    //When total reflection
    if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)
        return obj->emission + f * (radianceRT(reflRay,depth,scene));
    //otherwise, choose reflection or refraction
    Vec3d tdir = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();
    double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n));
    double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);
    //Russian roulette method to reduce the variance
    return obj->emission + f * (depth>2 ? (randRT()<P ? radianceRT(reflRay,depth,scene)*RP:radianceRT(Ray(x,tdir),depth, scene)*TP) : radianceRT(reflRay,depth,scene)*Re+radianceRT(Ray(x,tdir),depth,scene)*Tr);
}

void raytracing(Scene* scene, int samps, Ray camera, int w, int h, const char* outfile) {
    Vec3d cx = Vec3d(w*.5135/h);
    Vec3d cy = (cx^camera.d).norm()*.5135;
    Vec3d r;
    Vec3d *c = new Vec3d[w*h];
    
    #pragma omp parallel for schedule(dynamic, 1) private(r)
    for (int y=0; y<h; ++y) {
        fprintf(stderr,"\rRendering (%d samples per pixel) %5.2f%%",samps*4,100.*y/(h-1));
        for (unsigned short x=0; x<w; x++)
            //For every pixel, make a 2x2 sampling
            for (int sy=0, i=(h-y-1)*w+x; sy<2; sy++)
                for (int sx=0; sx<2; sx++, r=Vec3d()) {
                    for (int s=0; s<samps; s++) {
                        double r1=2*randRT(), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);
                        double r2=2*randRT(), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);
                        Vec3d d = cx*( ( (sx+.5 + dx)/2 + x)/w - .5) +
                        cy*( ( (sy+.5 + dy)/2 + y)/h - .5) + camera.d;
                        r = r + radianceRT(Ray(camera.o+d*140,d.norm()), 0, scene)*(1./samps);
                    }
                    c[i] = c[i] + Vec3d(clamp(r.x),clamp(r.y),clamp(r.z))*.25;
                }
    }
    
    FILE *f = fopen(outfile, "w");
    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
    for (int i=0; i<w*h; i++)
        fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
}
    
}//namespace engine
    
}//namespace rt
