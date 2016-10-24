#include "Scene.h"
#include <cstdio>

namespace rt {
    
Scene::Scene():size(0) {}
    
Scene::~Scene() {
    for (int i=0; i<size; ++i)
        delete objects[i];
}
    
void Scene::addObj(RTObject *p) {
    objects.push_back(p);
    ++size;
}
    
void Scene::removeObj(int index) {
    if (index >= size) {
        printf("RTError: Scene::removeObj is out of range!");
        return;
    }
    delete objects[index];
    objects.erase(objects.begin() + index);
    --size;
}
    
int Scene::getSize() const {
    return size;
}
    
RTObject* Scene::getObj(int index) const {
    if (index >= size) {
        printf("RTError: Scene::getObj is out of range!");
        return NULL;
    }
    return objects[index];
}
    
void Scene::clear() {
    for (int i=0; i<size; ++i)
        delete objects[i];
    objects.clear();
    size = 0;
}
    
}
