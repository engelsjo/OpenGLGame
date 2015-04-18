#include "Game.h"



using namespace std;

public void Game::init() {
    /* place the camera at Z=+5 (notice that the sign is OPPOSITE!) */
    /*camera_cf *= glm::translate(glm::vec3{0, 0, -100});
    camera_cf = glm::scale(glm::vec3 {.02,.02,.02}) * camera_cf;*/


    football.build();
    field.build();
    uprights.build();
    bleachers.build();

    //build the objects
    upright_cf = glm::translate(glm::vec3{0, 0, 0});
    bleacher_cf = glm::translate(glm::vec3{0, 160, 0});
    generate_conditions();


    //set the light sources
    /*light_cf = glm::translate(glm::vec3{-100, 100, 75});*/

    objects.push_back(make_pair(&field, field_cf));
    objects.push_back(make_pair(&football, football_cf));
    objects.push_back(make_pair(&uprights, uprights_cf));
    objects.push_back(make_pair(&bleachers, bleachers_cf));


    football_cf_values = (float*)glm::value_ptr(football_cf);

    //TODO: INITIALIZE STUFF
    pause = false;
    srand(time());
}

private glm::mat4x4 Game::generate_conditions() {
    int fx = rand(60) + 20;
    int y_limit = min(2*x, 160);
    int fy = rand(y_limit) - y_limit/2;

    football_cf = glm::translate(glm::vec3{fx, fy, .25});

    int wx = rand(20) - 10;
    int wy = rand(20) - 10;
    int wz = rand(6) - 3;

    wind_speed = glm::translate(glm::vec3{wx, wy, wz});
}


public void Game::update() {
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

public Game::Game(){
    init_gl();
}

public void Game::reset(){
    generate_conditions();
    score = -1;
}

public int Game::get_score() {
    return score;
}

public vector< pair< void*, glm::mat4x4 > > get_objects() {
    return objects;
}
