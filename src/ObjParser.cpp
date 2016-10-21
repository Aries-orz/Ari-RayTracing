#include "ObjParser.h"
#include <string.h>
#include <vector>
#include <stdio.h>

namespace rt {
    
ObjParser::ObjParser():numOfVertices(-1), numOfFaces(-1), verticeList(NULL), faceList(NULL) {}
    
ObjParser::~ObjParser() {destroy();}
    
void ObjParser::destroy() {
    if (verticeList)
        delete [] verticeList;
    if (faceList)
        delete [] faceList;
        
    numOfVertices = -1;
    numOfFaces = -1;
    verticeList = NULL;
    faceList = NULL;
}
    
bool ObjParser::readFromObj(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("RTError: The file %s doesn't exist.\n", filename);
        return false;
    } else {
        if (parse(fp)) {
            printf("Read from %s successfully.\n", filename);
            printf("Vertex Number = %d\n", numOfVertices);
            printf("Face Number = %d\n", numOfFaces);
            fclose(fp);
            return true;
        } else {
            printf("RTError: Cannot parse %s.\n", filename);
            fclose(fp);
            return false;
        }
    }
}
    
bool ObjParser::parse(FILE* fp) {
    char buf[256];
    int nVertices = 0, nFaces = 0;
    int lineNum = 0;
    std::vector<Vec3d> vecVertices;
    std::vector<TriArray> vecFaces;
    
    while (fscanf(fp, "%s", buf) != EOF) {
        ++lineNum;
        switch(buf[0]) {
            case '#':
                fgets(buf, sizeof(buf), fp);
                break;
            case 'v':
                switch(buf[1]) {
                    case '\0': {
                        Vec3d point;
                        if (fscanf(fp, "%lf %lf %lf", &point.x, &point.y, &point.z) == 3) {
                            ++nVertices;
                            vecVertices.push_back(point);
                        } else {
                            printf("RTError: Wrong data format at line %d.\n", lineNum);
                            return false;
                        }
                        break;
                    }
                    default:
                        fgets(buf, sizeof(buf), fp);
                        break;
                }
                break;
            case 'f':
                int v, n, t;
                TriArray indice;
                if (fscanf(fp, "%s", buf) != 1) {
                    printf("RTError: Wrong data format at line %d.\n", lineNum);
                    return false;
                }
                
                if (strstr(buf, "//")) {
                    if ( sscanf(buf, "%d//%d", &indice[0], &n) == 2 &&
                         fscanf(fp, "%d//%d", &indice[1], &n) == 2 &&
                         fscanf(fp, "%d//%d", &indice[2], &n) == 2 ) {
                        ++nFaces;
                        vecFaces.push_back(indice);
                    } else {
                        printf("RTError: Wrong data format at line %d.\n", lineNum);
                        return false;
                    }
                }
                
                else if (sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3) {
                    indice[0] = v;
                    if ( fscanf(fp, "%d/%d/%d", &indice[1], &t, &n) == 3 &&
                         fscanf(fp, "%d/%d/%d", &indice[2], &t, &n) == 3 ) {
                        ++nFaces;
                        vecFaces.push_back(indice);
                        }
                    else {
                        printf("RTError: Wrong data format at line %d.\n", lineNum);
                        return false;
                    }
                }
                else if (sscanf(buf, "%d/%d", &v, &t) == 2) {
                    indice[0] = v;
                    if ( fscanf(fp, "%d/%d", &indice[1], &t) == 2 &&
                         fscanf(fp, "%d/%d", &indice[2], &t) == 2 ) {
                        ++nFaces;
                        vecFaces.push_back(indice);
                    }
                    else {
                        printf("RTError: Wrong data format at line %d.\n", lineNum);
                        return false;
                    }
                }
                else {
                    if ( sscanf(buf, "%d", &indice[0]) == 1 &&
                         fscanf(fp, "%d", &indice[1]) == 1 &&
                         fscanf(fp, "%d", &indice[2]) == 1 ) {
                        ++nFaces;
                        vecFaces.push_back(indice);
                    }
                    else {
                        printf("RTError: Wrong data format at line %d.\n", lineNum);
                        return false;
                    }
                }
                break;
            default:
                fgets(buf, sizeof(buf), fp);
                break;
        }
    }
    
    for (int i=0; i<vecFaces.size(); ++i) {
        TriArray tri = vecFaces[i];
        for (int j=0; j<3; ++j) {
            if (tri[j] <=0 || tri[j] > nVertices) {
                printf("RTError: The vertex index of face at line %d is out of range!\n", lineNum);
                return false;
            }
        }
    }
    destroy();
    numOfVertices = nVertices;
    numOfFaces = nFaces;
    verticeList = new Vec3d[numOfVertices];
    faceList = new TriArray[numOfFaces];
    for (int i=0; i<numOfVertices; ++i) {
        verticeList[i] = vecVertices[i];
    }
    for (int i=0; i<numOfFaces; ++i) {
        for (int j=0; j<3; ++j)
            faceList[i][j] = vecFaces[i][j] - 1;
    }
    
    return true;
}
    
}
