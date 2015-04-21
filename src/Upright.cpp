//
//  Upright.cpp
//  Project4
//
//  Created by Joshua Engelsma on 4/18/15.
//
//

//
//  HeliBase.cpp
//  ProjectTwo
//
//  Created by Joshua Engelsma on 3/11/15.
//
//

#include "Upright.h"
#include <math.h>


void Upright::build (void*)
{
    base.build("Polished Gold");
    cross_bar.build("Polished Gold");
    upright1.build("Polished Gold");
    upright2.build("Polished Gold");
}


void Upright::render(bool)
{
    //base bar
    glPushMatrix();
    glTranslatef(0, 0, 0);
    base.render(1, 1, 10);
    glPopMatrix();
    
    //cross bar
    glPushMatrix();
    glTranslatef(-9.25, 0, 10);
    glRotatef(90.0, 0, 1, 0);
    cross_bar.render(1,1,18.5);
    glPopMatrix();
    
    //upright 1
    glPushMatrix();
    glTranslatef(-9.25, 0, 10);
    upright1.render(1, 1, 20);
    glPopMatrix();
    
    //upright 2
    glPushMatrix();
    glTranslatef(9.25, 0, 10);
    upright2.render(1, 1, 20);
    glPopMatrix();
}

