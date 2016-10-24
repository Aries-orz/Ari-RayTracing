#include <cstdlib>
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

const int w = 1024; //width of the final picture
const int h = 768; //height of the final picture

void generateWorld(Scene& scene) {
    //Add the walls
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
    scene.addObj(new RTSphere(Vec3d(45,12,120),    Vec3d(), Vec3d(1,1,1)*.999, 12, RTObject::REFRACTIVE));
    scene.addObj(new RTSphere(Vec3d(27,52.001,47), Vec3d(), Vec3d(1,1,1)*.999, 12, RTObject::DIFFUSE));

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
    RTBBox *bbox = new RTBBox(Vec3d(53,0,68), Vec3d(93,20,88)); //Add a bounding box for the complex object
    scene.addObj(new RTComplexObj(indices, bbox, num, RTObject::DIFFUSE, Vec3d(), Vec3d(0,0,1)));
}

int main(int argc, char* argv[]) {
    Scene scene;
    generateWorld(scene);
    
    //Make a 2x2 sampling
    int samps = (argc==2 ? atoi(argv[1])/4 : 1);
    //Initialize the camera
    Ray camera(Vec3d(50, 52, 295.6), Vec3d(0, -0.042612, -1).norm());
    
    //Start the ray tracing
    engine::raytracing(&scene, samps, camera, w, h, "result.ppm");
    
}




