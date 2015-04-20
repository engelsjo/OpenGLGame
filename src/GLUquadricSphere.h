#ifndef GLUQUADRICSPHERE_H
#define GLUQUADRICSPHERE_H

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <string>
using namespace std;
class GLUquadricSphere{

public:
    string MATERIAL = "Emerald";
    float AMBIENT[4];
    float DIFFUSE[4];
    float SPECULAR[4];
    float SHININESS;
    GLUquadric* q_cyl;
    void build(string mat);
    void render(float rad);
};

#endif // GLUQUADRICSPHERE_H
