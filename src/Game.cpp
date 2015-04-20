#include "Game.h"

using namespace std;

void Game::init() {
    /* place the camera at Z=+5 (notice that the sign is OPPOSITE!) */
    /*camera_cf *= glm::translate(glm::vec3{0, 0, -100});
     camera_cf = glm::scale(glm::vec3 {.02,.02,.02}) * camera_cf;*/
    
    
    football.build(nullptr);
    uprights.build(nullptr);
    bleachers.build(nullptr);
    bleachers1.build(nullptr);
    uprights1.build(nullptr);
    
    //build the objects
    uprights_cf = glm::translate(glm::vec3{0, 175, 0});
    bleachers_cf = glm::translate(glm::vec3{100, 0, 0});
    bleachers1_cf = glm::rotate(glm::radians(180.0f), glm::vec3{0, 0, 1});
    bleachers1_cf *= glm::translate(glm::vec3{100, 0, 0});
    uprights1_cf = glm::translate(glm::vec3{0, -175, 0});
    generate_conditions();
    
    
    //set the light sources
    /*light_cf = glm::translate(glm::vec3{-100, 100, 75});*/
    objects.push_back(make_pair(&football, football_cf));
    objects.push_back(make_pair(&uprights, uprights_cf));
    objects.push_back(make_pair(&bleachers, bleachers_cf));
    objects.push_back(make_pair(&bleachers1, bleachers1_cf));
    objects.push_back(make_pair(&uprights1, uprights1_cf));
    
    
    football_cf_values = (float*)glm::value_ptr(football_cf);
    
    //TODO: INITIALIZE STUFF
    srand(time(NULL));
}

void Game::generate_conditions() {
    int fx = rand()%60 + 20;
    int y_limit = min(2*fx, 160);
    int fy = rand()%y_limit - y_limit/2;
    
    football_cf = glm::translate(glm::vec3{fx, fy, .25});
    
    int wx = rand()%20 - 10;
    int wy = rand()%20 - 10;
    int wz = rand()%6 - 3;
    
    wind_speed = glm::vec3{wx, wy, wz};
}


void Game::update() {
    float elapsed_time = timer.elapsed() * 1000;
    timer.reset();
    
    football_cf *= glm::translate(elapsed_time * (football_speed + wind_speed));
    football_speed += elapsed_time * GRAVITY;
    
    football_cf = glm::rotate(elapsed_time, glm::vec3{0, 1, 0});
    
    if(football_cf_values[3] <= 0) {
        //check for field goal
        if(football_cf_values[11] > 20 && abs(football_cf_values[7]) < 10) {
            score = glm::length(wind_speed) + 20;
        }
        else {
            score = 0;
        }
    }
    else if(football_cf_values[11] <= 0) {
        //hit ground, too short
        score = 0;
        football_speed = glm::vec3{0,0,0};
    }
}

void Game::reset(){
    generate_conditions();
    score = -1;
}

int Game::get_score() {
    return score;
}

vector< pair< void*, glm::mat4x4 > > Game::get_objects() {
    return objects;
}