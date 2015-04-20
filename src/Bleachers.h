//
//  Bleachers.h
//  Project4
//
//  Created by Joshua Engelsma on 4/18/15.
//
//

#ifndef __Project4__Bleachers__
#define __Project4__Bleachers__
#include "Cube.h"

class Bleachers : public BufferObject {
protected:
public:
    void build (void*);
    void render(bool);
    Cube row;
    Cube backe;
    Cube mide;
};

#endif /* defined(__Project4__Bleachers__) */

