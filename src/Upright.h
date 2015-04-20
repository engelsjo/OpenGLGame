//
//  Upright.h
//  Project4
//
//  Created by Joshua Engelsma on 4/18/15.
//
//

#ifndef __Project4__Upright__
#define __Project4__Upright__

#include <stdio.h>
#include "BufferObject.h"
#include "GLUquadricCylinder.h"

class Upright : public BufferObject {
protected:
public:
    void build (void*);
    void render(bool);
    GLUquadricCylinder base;
    GLUquadricCylinder cross_bar;
    GLUquadricCylinder upright1;
    GLUquadricCylinder upright2;
};
#endif /* defined(__Project4__Upright__) */
