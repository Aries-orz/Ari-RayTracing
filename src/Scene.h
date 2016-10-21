#pragma once

#include <vector>
#include "RTObject.h"

namespace rt {
    
class Scene {
protected:
    std::vector<RTObject*> objects;
    int size;
    
public:
    Scene();
    ~Scene();
    
    void addObj(RTObject* p);
    void removeObj(int index);
    int getSize() const;
    RTObject* getObj(int index) const;
    void clear();
};
    
}
