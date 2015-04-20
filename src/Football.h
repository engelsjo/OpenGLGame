//
//  Football.h
//  Project4
//
//  Created by Joshua Engelsma on 4/18/15.
//
//

#ifndef __Project4__Football__
#define __Project4__Football__

#include "BufferObject.h"
#include "GLUquadricCylinder.h"


class Football : public BufferObject {
protected:
public:
    void build (void*);
    void render(bool);
    GLUquadricCylinder front_half;
    GLUquadricCylinder back_half;
};

#endif /* defined(__Project4__Football__) */
