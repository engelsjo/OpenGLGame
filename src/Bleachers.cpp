//
//  Bleachers.cpp
//  Project4
//
//  Created by Joshua Engelsma on 4/18/15.
//
//

#include "Bleachers.h"


void Bleachers::build (void*)
{
    row.build_with_params(5, 5, 300, "Chrome");
    backe.build_with_params(125, 5, 300, "Chrome");
    mide.build_with_params(65, 5, 300, "Chrome");
}


void Bleachers::render(bool)
{
    for(int i = 0; i < 25; i++){
        glPushMatrix();
        glTranslatef(i*5, 0, i*5);
        row.render(false);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(125, 0, 62.5);
    backe.render(false);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(65, 0, 32.5);
    mide.render(false);
    glPopMatrix();

}
