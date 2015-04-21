#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <chrono>
#include "Timer.hpp"
#include <cmath>
#include <algorithm>
#include <ctime>
#include <time.h>
#include <vector>

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
#include "Upright.h"
#include "Bleachers.h"

class Game {
private:
    Timer timer;
    
    vector<std::pair<void*, glm::mat4x4*>>* objects;
    
    Football football;
    Upright uprights;
    Bleachers bleachers;
    Bleachers bleachers1;
    Upright uprights1;
    
    glm::mat4 camera_cf, light_cf;
    glm::mat4 football_cf, uprights_cf, uprights1_cf, bleachers_cf, bleachers1_cf, field_cf;
    
    glm::vec3 wind_speed;
    glm::vec3 football_speed;
    glm::vec3 GRAVITY = glm::vec3{0, 0, -9.81};
    
    float *football_cf_values;
    
    int score;
    bool is_kicked;
    
    void generate_conditions();
    void check_collisions();
    
public:
    void init();
    void update();
    int get_score();
    void reset();
    vector< pair<void*, glm::mat4x4*> >* get_objects();
    void kick( glm::vec3 );
    glm::vec3 get_wind_speed();
};

#endif // GAME_H_INCLUDED