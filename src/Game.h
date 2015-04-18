#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <chrono>
#include "Timer.hpp"
#include <cmath>
#include <algorithm>
#include <ctime>
#include <time.h>

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <stdlib.h>
#include "Cube.h"
#include "Football.h"
#include "Uprights.h"
#include "Bleachers.h"

class Game {
private:
    static Timer timer;

    vector<void*, glm::mat4x4> objects;

    Cube field;
    Football football;
    Uprights uprights;
    Bleachers bleachers;

    glm::mat4 camera_cf, light_cf;
    glm::mat4 football_cf, uprights_cf, bleachers_cf, field_cf;

    glm::vec3 wind_speed;
    glm::vec3 football_speed;
    static const glm::vec3 GRAVITY = glm::vec3{0, 0, -9.81};

    float *football_cf_values;

    int last_score;

    void init();
    void generate_conditions();
    void check_collisions();

public:
    Game();
    void update();
    int get_score();
    void reset();
    int get_score();
    vector< pair<void*, glm::mat4x4> > get_objects();

};

#endif // GAME_H_INCLUDED
