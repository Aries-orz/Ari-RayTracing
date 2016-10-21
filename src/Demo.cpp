#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "Vec3d.h"
#include "Ray.h"
#include "RTSphere.h"
#include "RTBox.h"
#include "RTBBox.h"
#include "RTTriangle.h"
#include "ObjParser.h"
#include "Scene.h"
#include "RTPlane.h"
#include "Engine.h"
#include "RTComplexObj.h"
using namespace rt;

const int w = 1024;
const int h = 768;

inline double clamp(double x) {
    return x<0 ? 0 : x>1 ? 1 : x;
}

inline int toInt(double x) {
    return int(pow(clamp(x), 1/2.2) * 255 + .5);
}

void generateWorld(Scene& scene) {
    //Add walls
    scene.addObj(new RTPlane(Vec3d(1, 0, 0), Vec3d(1, 0, 0), RTObject::DIFFUSE, Vec3d(), Vec3d(.75, .25, .25)));//left
    scene.addObj(new RTPlane(Vec3d(99, 0, 0), Vec3d(-1, 0, 0), RTObject::DIFFUSE, Vec3d(), Vec3d(.25, .75, .25)));//right
    scene.addObj(new RTPlane(Vec3d(0, 0, 0), Vec3d(0, 0, 1), RTObject::REFRACTIVE, Vec3d(), Vec3d(1, 1, 1)));//back
    scene.addObj(new RTPlane(Vec3d(0, 0, 300), Vec3d(0, 0, -1), RTObject::REFRACTIVE, Vec3d(), Vec3d()));//front
    scene.addObj(new RTPlane(Vec3d(0, 0, 0), Vec3d(0, 1, 0), RTObject::DIFFUSE, Vec3d(), Vec3d(.75, .75, .75)));//bottom
    scene.addObj(new RTPlane(Vec3d(0, 81.6, 0), Vec3d(0, -1, 0), RTObject::DIFFUSE, Vec3d(), Vec3d(.75, .75, .75)));//top
    
    //Add the light
    scene.addObj(new RTTriangle(Vec3d(40, 81.6-.01, 70), Vec3d(60, 81.6-.01, 70), Vec3d(40, 81.6-.01, 90),
                                RTObject::DIFFUSE, Vec3d(12, 12, 12), Vec3d()));
    scene.addObj(new RTTriangle(Vec3d(60, 81.6-.01, 90), Vec3d(60, 81.6-.01, 70), Vec3d(40, 81.6-.01, 90),
                                RTObject::DIFFUSE, Vec3d(12, 12, 12), Vec3d()));
    
    //Add two sphere
    scene.addObj(new RTSphere(Vec3d(45,12,120), 		Vec3d(),         Vec3d(1,1,1)*.999,  12,   RTObject::REFRACTIVE));
    scene.addObj(new RTSphere(Vec3d(27,52.001,47), 	    Vec3d(),         Vec3d(1,1,1)*.999,  12,   RTObject::DIFFUSE));

    //Add one box
    scene.addObj(new RTBox(Vec3d(10.5,0,30.5), Vec3d(43.5,40,63.5), RTObject::DIFFUSE, Vec3d(), Vec3d(1,1,1)*.999));
    
    //Parse the .obj file
    ObjParser parser;
    parser.readFromObj("test_data/block.obj");
    int num = parser.numOfFaces;
    
    //Add the block object
    RTTriangle* indices = new RTTriangle[num];
    for (int i=0; i<num; ++i) {
        Vec3d p0 = parser.verticeList[parser.faceList[i][0]];
        Vec3d p1 = parser.verticeList[parser.faceList[i][1]];
        Vec3d p2 = parser.verticeList[parser.faceList[i][2]];
        indices[i] = RTTriangle(p0+Vec3d(73,10,79), p1+Vec3d(73,10,79), p2+Vec3d(73,10,79), RTObject::DIFFUSE, Vec3d(), Vec3d(0,0,1));
    }
    RTBBox *bbox = new RTBBox(Vec3d(53,0,68), Vec3d(93,20,88));
    scene.addObj(new RTComplexObj(indices, bbox, num, RTObject::DIFFUSE, Vec3d(), Vec3d(0,0,1)));
}

int main(int argc, char* argv[]) {
    Scene scene;
    generateWorld(scene);
    
    int samps = (argc==2 ? atoi(argv[1])/4 : 1);
    Ray cam(Vec3d(50, 52, 295.6), Vec3d(0, -0.042612, -1).norm());
    Vec3d cx = Vec3d(w*.5135/h), cy = (cx^cam.d).norm()*.5135, r, *c = new Vec3d[w*h];
    
#pragma omp parallel for schedule(dynamic, 1) private(r)
    for (int y=0; y<h; ++y) {
        fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1));
        for (unsigned short x=0; x<w; x++)
            //对每个像素点，作一个2*2的二次采样，每次采样取samps个样本
            for (int sy=0, i=(h-y-1)*w+x; sy<2; sy++)
                for (int sx=0; sx<2; sx++, r=Vec3d()) {
                    for (int s=0; s<samps; s++) {
                        double r1=2*Engine::randRT(), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);
                        double r2=2*Engine::randRT(), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);
                        Vec3d d = cx*( ( (sx+.5 + dx)/2 + x)/w - .5) +
                        cy*( ( (sy+.5 + dy)/2 + y)/h - .5) + cam.d;
                        r = r + Engine::radianceRT(Ray(cam.o+d*140,d.norm()), 0, scene)*(1./samps);
                    }
                    c[i] = c[i] + Vec3d(clamp(r.x),clamp(r.y),clamp(r.z))*.25;
                }
    }
    
    FILE *f = fopen("result.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
    for (int i=0; i<w*h; i++)
        fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
    
}




