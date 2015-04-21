#ifndef MY_TORUS_H
#define MY_TORUS_H
#include <vector>
#include <GL/glew.h>
#include "Shader.h"
using namespace std;

class Plane {
private:
    GLuint vertex_buffer, index_buffer, normal_buffer;
public:
    void build_with_params(float length, float width);
    void render(Shader* s) const;
};
#endif
