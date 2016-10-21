#pragma once

#include <stdio.h>
#include "Vec3d.h"

namespace rt {
    
class ObjParser {
public:
    struct TriArray {
        int a, b, c;
        int& operator[] (const int i) {
            switch (i) {
                case 0: return a;
                case 1: return b;
                case 2: return c;
                default: {
                    printf("RTError: The TriArray index is out of range!");
                    return a;
                }
            }
        }
    };
    
    int numOfVertices;
    int numOfFaces;
    Vec3d* verticeList;
    TriArray* faceList;
    
public:
    ObjParser();
    ~ObjParser();
    
    bool isLoaded();
    void destroy();
    bool readFromObj(const char* filename);
    
protected:
    bool parse(FILE* p);
    
};
    
}