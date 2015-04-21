#include "Football.h"
#include <cmath>
#include <iostream>
#include <glm/trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>
#define SCALE 50.0

void Football::build () {
    vector<GLushort> indices;
    vector<GLfloat> vertices, normals;

    for(int i = -5; i <= 5; i++) {
        float x = i/10.0;
        float r =  sqrt(.125 - .5 * x * x);

        for(int j = -5; j <= 5; j++) {
            float y = r / 5.0 * j;
            float z = sqrt(r*r - y*y);
            vertices.push_back(x * SCALE);
            vertices.push_back(y * SCALE);
            vertices.push_back(z * SCALE);

            glm::vec3 n {x, y, z};
            glm::normalize(n);

            normals.push_back(n.x);
            normals.push_back(n.y);
            normals.push_back(n.z);
        }
        for(int j = 4; j >= -4; j--) {
            float y = r / 5.0 * j;
            float z = -sqrt(r*r - y*y);
            vertices.push_back(x * SCALE);
            vertices.push_back(y * SCALE);
            vertices.push_back(z * SCALE);

            glm::vec3 n {x, y, z};
            glm::normalize(n);

            normals.push_back(n.x);
            normals.push_back(n.y);
            normals.push_back(n.z);
        }
    }

    for(int k = 1; k < 10; k++) {
        for(int p = 0; p < 19; p++) {
            indices.push_back(k * 20 + p);
            indices.push_back((k + 1) * 20 + p);
            indices.push_back(k * 20 + p + 1);

            indices.push_back(k * 20 + p);
            indices.push_back(k * 20 + p + 1);
            indices.push_back((k - 1) * 20 + p + 1);
        }

        indices.push_back(k * 20 + 19);
        indices.push_back((k + 1) * 20 + 19);
        indices.push_back(k * 20 + 0);

        indices.push_back(k * 20 + 19);
        indices.push_back(k * 20 + 0);
        indices.push_back((k - 1) * 20 + 0);
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

void Football::render(Shader* s) const {
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
    for (int k = 0; k < 40 * 9; k++) {
        /* each triangle must be rendered using a separate call */
        glDrawElements(GL_TRIANGLES, N,
                GL_UNSIGNED_SHORT, ptr);
        ptr += N;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopAttrib();
}
