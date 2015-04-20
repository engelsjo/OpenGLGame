#ifndef GLUQUADRICCYLINDER_H
#define GLUQUADRICCYLINDER_H

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <string>
using namespace std;
class GLUquadricCylinder{

public:
    string MATERIAL = "Copper";
    float AMBIENT[4];
    float DIFFUSE[4];
    float SPECULAR[4];
    float SHININESS;
    GLUquadric* q_cyl;
    void build(string mat);
    void render(float topr, float botr, float height);
};

#endif // GLUQUADRICCYLINDER_H