#include "Engine.h"
#include <math.h>

namespace rt {

Vec3d Engine::radianceRT(const Ray &r, int depth, Scene& scene) {
    double tmin = 0;
    int id = 0;
    int objSize = scene.getSize();
    for (int i=0; i<objSize; ++i) {
        double t = scene.getObj(i)->hit(r);
        if (!t) continue;
        if (t < tmin || !tmin) {
            tmin = t;
            id = i;
        }
    }
    if (!tmin) return Vec3d();
        
    Vec3d x = r.o + r.d * tmin;
    RTObject *obj = scene.getObj(id);
    Vec3d n = obj->getNormal(r, tmin);
    Vec3d nl = n.dot(r.d)<0 ? n : n*-1;
    Vec3d f = obj->color;
    double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z;
        
    if (depth > 100) return obj->emission;
    if (++depth > 5) {
        if (randRT() < p) f = f * (1/p);
        else return obj->emission;
    }
    //漫反射
    if (obj->mat == RTObject::DIFFUSE) {
            double r1 = 2 * M_PI * randRT();
            double r2 = randRT(), r2s = sqrt(r2);
            Vec3d w = nl, u = ((fabs(w.x)>.1 ? Vec3d(0,1,0) : Vec3d(1,0,0))^w).norm(), v = w^u;
            Vec3d d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
            return obj->emission + f * (radianceRT(Ray(x,d), depth, scene));
        }
        //镜面反射
        else if (obj->mat == RTObject::SPECULAR)
            return obj->emission + f * (radianceRT(Ray(x, r.d-n*2*n.dot(r.d)), depth, scene));
        //折射
        Ray reflRay(x, r.d-n*2*n.dot(r.d));
        bool into = n.dot(nl)>0;
        double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.d.dot(nl), cos2t;
        //当全反射时
        if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)
            return obj->emission + f * (radianceRT(reflRay,depth,scene));
        //否则，选择反射或者折射
        Vec3d tdir = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();
        double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n));
        double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);
        //Russian roulette方法（蒙特卡洛中一种减小方差的技巧）
        return obj->emission + f * (depth>2 ? (randRT()<P ? radianceRT(reflRay,depth,scene)*RP:radianceRT(Ray(x,tdir),depth, scene)*TP) : radianceRT(reflRay,depth,scene)*Re+radianceRT(Ray(x,tdir),depth,scene)*Tr);
    }

}
