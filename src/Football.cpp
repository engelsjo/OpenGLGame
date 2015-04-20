//
//  Football.cpp
//  Project4
//
//  Created by Joshua Engelsma on 4/18/15.
//
//

#include "Football.h"
#define VISIBLE_SCALAR 3

void Football::build(void*){
    front_half.build("Bronze");
    back_half.build("Bronze");
}

void Football::render(bool){
    glPushMatrix();
    glTranslatef(0, 0, .5 * VISIBLE_SCALAR);
    front_half.render(.6 * VISIBLE_SCALAR, .15 * VISIBLE_SCALAR, .5 * VISIBLE_SCALAR);
    glPopMatrix();

    glPushMatrix();
    back_half.render(.15 * VISIBLE_SCALAR, .6 * VISIBLE_SCALAR, .5 * VISIBLE_SCALAR);
    glPopMatrix();

}
