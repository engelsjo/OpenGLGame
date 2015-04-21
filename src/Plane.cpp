#include "Plane.h"
#include <cmath>
#include <iostream>
#include <glm/trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>

void Plane::build_with_params (float length, float width)) {
    vector<GLushort> indices;
    vector<GLfloat> vertices, normals;

    for(int l = 0; l <= 20; l++) {
        for(int w = 0; w <= 20; w++) {
            float x = length/20.0 * l;
            float y = width/20.0 * w;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(0);
            normals.push_back(0);
            normals.push_back(0);
            normals.push_back(1);
        }
    }


    for(int l = 0; l < 20; l++) {
        for(int w = 0; w < 20; w++) {
            indices.push_back(21 * l + w);
            indices.push_back(21 * l + w + 1);
            indices.push_back(21 * (l + 1) + w + 1);

            indices.push_back(21 * l + w);
            indices.push_back(21 * (l + 1) + w + 1);
            indices.push_back(21 * (l + 1) + w);
        }
    }

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Plane::render(Shader* s) const {
    glPushAttrib(GL_ENABLE_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    if (glIsBuffer(normal_buffer)) {
        //glEnableClientState(GL_NORMAL_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
        glNormalPointer(GL_FLOAT, 0, 0);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    GLushort *ptr = 0;
    const int N = 3; // + (fullTorus ? 2 : 0);
    for (int k = 0; k < 2 * 20 * 20; k++) {
        /* each triangle must be rendered using a separate call */
        glDrawElements(GL_TRIANGLE, N,
                GL_UNSIGNED_SHORT, ptr);
        ptr += N;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopAttrib();
}
