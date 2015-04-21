#include <iostream>
#include <chrono>
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

#undef GLFW_DLL
#include <GLFW/glfw3.h>

#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <math.h>
#include <stdlib.h>
#include "Upright.h"
#include "Bleachers.h"
#include "Football.h"
#include "Game.h"
#include "GLUquadricSphere.h"

void init_model();
void win_refresh(GLFWwindow*);
float arc_ball_rad_square;
int screen_ctr_x, screen_ctr_y;

float time_elapsed;
static Timer timer;

glm::mat4 camera_cf, light1_cf, light0_cf;

/* light source setting */
GLfloat light0_color[] = {1.0, 1.0, 1.0, 1.0};   /* color */
GLfloat light1_color[] = {1.0, 1.0, 0.8, 1.0};  /* color */
GLfloat black_color[] = {0.0, 0.0, 0.0, 1.0};   /* color */

Game model;
GLUquadricSphere ball;

//image path
const string TOP_DIR = "/Users/joshuaengelsma/Documents/CIS-367/Project4/";

Shader * football_shader;
unsigned char* football_texture;
GLuint texId;

vector< pair< void*, glm::mat4x4* > >* objects;



using namespace std;
void err_function (int what, const char *msg) {
    cerr << what << " " << msg << endl;
}

void initShaders() {
    int img_width, img_height, channels;
    football_texture = stbi_load((TOP_DIR + "images/football.jpg").c_str(),
                       &img_width, &img_height, &channels, 3);
    
    printf ("Image size is %dx%d\n", img_width, img_height);
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 img_width, img_height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 football_texture);
    
    glBindTexture (GL_TEXTURE_2D, 0);
    
    try {
        football_shader = new Shader(TOP_DIR + "vshader-football.vs",
                               TOP_DIR + "fshader-football.fs");
        
        
        static float c1[] = {0.3529f, 0.745f, 0.3529f, 1.0f,
            0.9333, 0.0, 0.0, 1.0};
        football_shader->use();
     
        //int u1 = glGetUniformLocation(football_shader->id(), "colors");
        //glUniform4fv(u1, 8, c1);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texId);
        int tex_handle = glGetUniformLocation(football_shader->id(), "football_tex");
        glUniform1i(tex_handle, 0);
    }
    catch (const char* s) {
        cerr << "Shader init error: " << s << endl;
    }
}

void win_resize (GLFWwindow * win, int width, int height)
{
#ifdef DEBUG
    cout << __FUNCTION__ << " " << width << "x" << height << endl;
#endif
    int w, h;
    glfwGetWindowSize(win, &w, &h);
    screen_ctr_x = w / 2.0;
    screen_ctr_y = h / 2.0;
    float rad = min(h,w)/2;
    arc_ball_rad_square = rad * rad;
    /* Use the entire window for our view port */
    glViewport(0, 0, width, height);
    /* Use GL_PROJECTION to select the type of synthetic camera */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    /* near-plane(1) & far-plane(10) are always POSITIVE and they measure
     * the distances along the Z-axis in front of the camera */
    gluPerspective(60.0, static_cast<float> (width)/ static_cast<float> (height), 1, 10);
}

void win_refresh (GLFWwindow *win) {
    
    //    cout << __PRETTY_FUNCTION__ << endl;
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    
    /* place the camera using the camera coordinate frame */
    glMultMatrixf (glm::value_ptr(camera_cf));
    
    
    /* Specify the reflectance property of the ground using glColor
     (instead of glMaterial....)
     */
    glEnable (GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor3ub (29, 100, 56);
    
    glBegin (GL_QUADS);
    const int FIELD_WIDTH = 225;
    const int FIELD_LENGTH = 200;
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (FIELD_WIDTH, FIELD_LENGTH);
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (-FIELD_WIDTH, FIELD_LENGTH);
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (-FIELD_WIDTH, -FIELD_LENGTH);
    glNormal3f (0.0f, 0.0f, 1.0f); /* normal vector for the ground */
    glVertex2i (FIELD_WIDTH, -FIELD_LENGTH);
    glEnd();
    glDisable (GL_COLOR_MATERIAL);
    
    
    /* place the light source in the scene. */
    glLightfv (GL_LIGHT0, GL_POSITION, glm::value_ptr(glm::column(light0_cf, 3)));
    
    /* recall that the last column of a CF is the origin of the CF */
    glm::vec4 point_s = glm::vec4{50, 50, 50, 1}; //top of spotlight
    
    glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(point_s));
    
    /* we use the Z-axis of the light CF as the spotlight direction */
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, glm::value_ptr(glm::column(light1_cf, 2)));
    
    if (objects != NULL){
        model.update();
        int score = model.get_score();
        
        if (score != -1){ //we need to act... something happened
            if (score == 0){
                //you suck.. you missed
                std::cout << "You missed" << std::endl;
                model.reset();
                
            }else{
                //you scored some points
                std::cout << "you scored " << score << " " << endl;
                model.reset();
            }
        }
        
    }
    
    
    if (objects == NULL){}
    else{
        Football* football = (Football*)objects->at(0).first;
        Upright* upright = (Upright*)objects->at(1).first;
        Bleachers* bleacher = (Bleachers*)objects->at(2).first;
        Bleachers* bleacher1 = (Bleachers*)objects->at(3).first;
        Upright* upright1 = (Upright*)objects->at(4).first;
    
        //coord frames
        glm::mat4x4 mat1 = (*objects->at(0).second);
        glm::mat4x4 mat2 = (*objects->at(1).second);
        glm::mat4x4 mat3 = (*objects->at(2).second);
        glm::mat4x4 mat4 = (*objects->at(3).second);
        glm::mat4x4 mat5 = (*objects->at(4).second);
    
        glUseProgram(0);
        glPushMatrix();
        cout << "translating" << endl;
        glMultMatrixf(glm::value_ptr(mat1));
        football_shader->use();
        (*football).render(football_shader);
        glUseProgram(0);
        glPopMatrix();
    
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mat2));
        (*upright).render(false);
        glPopMatrix();
    
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mat3));
        (*bleacher).render(false);
        glPopMatrix();
        
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mat4));
        (*bleacher1).render(false);
        glPopMatrix();
        
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mat5));
        (*upright1).render(false);
        glPopMatrix();
    }
    
    
    /* must swap buffer at the end of render function */
    glfwSwapBuffers(win);
}

void init_gl() {
    
    
    //set up shading / lighting
    glClearColor (0.0, 0.0, 0.0, 1.0); /* black background */
    
    /* fill front-facing polygon */
    glPolygonMode (GL_FRONT, GL_FILL);
    /* draw outline of back-facing polygon */
    glPolygonMode (GL_BACK, GL_LINE);
    
    /* Enable shading */
    glEnable (GL_LIGHTING);
    glEnable (GL_NORMALIZE); /* Tell OpenGL to renormalize normal vector
                              after transformation */
    
    /* initialize two light sources */
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT0, GL_AMBIENT, light0_color);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_color);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light0_color);
    glEnable (GL_LIGHT1);
    glLightfv (GL_LIGHT1, GL_AMBIENT, light1_color);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light1_color);
    glLightfv (GL_LIGHT1, GL_SPECULAR, light1_color);
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 40); //spot light
    
    glEnable (GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glLineWidth(3.0);
    
    /* place the camera at Z=+5 (notice that the sign is OPPOSITE!) */
    camera_cf = glm::translate(glm::vec3{0, 275, -175}) * camera_cf;
    //camera_cf = glm::rotate(glm::radians(-45.0f), glm::vec3{0, 0, 1}) * camera_cf;
    camera_cf = glm::rotate(glm::radians(-60.0f), glm::vec3{1, 0, 0}) * camera_cf;
    camera_cf = glm::scale(glm::vec3 {.02,.02,.02}) * camera_cf;
    
    initShaders();
    
    
    model.init();
    objects = model.get_objects();
    ball.build("Copper");
    
}

void make_model() {
    time_elapsed = 0;
    //build object models
    
    //set the light sources
    light0_cf = glm::translate(glm::vec3{-100, 100, 75});
    
    light1_cf = glm::translate(glm::vec3{3.5, 0, 1}) * glm::rotate(glm::radians(180.0f), glm::vec3{1, 0, 0});
    
}

/* action: GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT */
void key_handler (GLFWwindow *win, int key, int scan_code, int action, int mods)
{
    //cout << __FUNCTION__ << endl;
    if (action != GLFW_PRESS) return;
    if (mods == GLFW_MOD_SHIFT) {
        switch(key) {
                
        }
    }
    else {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(win, true);
                break;
            case GLFW_KEY_RIGHT:
                camera_cf = glm::translate(glm::vec3{-.05, 0, 0}) * camera_cf;
                break;
            case GLFW_KEY_LEFT:
                camera_cf = glm::translate(glm::vec3{.05, 0, 0}) * camera_cf;
                break;
            case GLFW_KEY_UP:
                camera_cf = glm::translate(glm::vec3{0, -.05, 0}) * camera_cf;
                break;
            case GLFW_KEY_DOWN:
                camera_cf = glm::translate(glm::vec3{0, .05, 0}) * camera_cf;
                break;
            case GLFW_KEY_0:
                model.kick(glm::vec3{0, 50, 150});
                break;
        }
    }
    win_refresh(win);
}

/*
 The virtual trackball technique implemented here is based on:
 https://www.opengl.org/wiki/Object_Mouse_Trackball
 */
void cursor_handler (GLFWwindow *win, double xpos, double ypos) {
    int state = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT);
    static glm::vec3 first_click;
    static glm::mat4 current_cam;
    static bool is_tracking = false;
    
    glm::vec3 this_vec;
    if (state == GLFW_PRESS) {
        /* TODO: use glUnproject? */
        float x = (xpos - screen_ctr_x);
        float y = -(ypos - screen_ctr_y);
        float hypot_square = x * x + y * y;
        float z;
        
        /* determine whether the mouse is on the sphere or on the hyperbolic sheet */
        if (2 * hypot_square < arc_ball_rad_square)
            z = sqrt(arc_ball_rad_square - hypot_square);
        else
            z = arc_ball_rad_square / 2.0 / sqrt(hypot_square);
        if (!is_tracking) {
            /* store the mouse position when the button was pressed for the first time */
            first_click = glm::normalize(glm::vec3{x, y, z});
            current_cam = camera_cf;
            is_tracking = true;
        }
        else {
            /* compute the rotation w.r.t the initial click */
            this_vec = glm::normalize(glm::vec3{x, y, z});
            /* determine axis of rotation */
            glm::vec3 N = glm::cross(first_click, this_vec);
            
            /* determine the angle of rotation */
            float theta = glm::angle(first_click, this_vec);
            
            /* create a quaternion of the rotation */
            glm::quat q{cos(theta / 2), sin(theta / 2) * N};
            /* apply the rotation w.r.t to the current camera CF */
            camera_cf = current_cam * glm::toMat4(glm::normalize(q));
        }
        win_refresh(win);
    }
    else {
        is_tracking = false;
    }
}

void scroll_handler (GLFWwindow *win, double xscroll, double yscroll) {
    /* translate along the camera Z-axis */
    glm::mat4 z_translate = glm::translate((float)yscroll * glm::vec3{0, 0, .05});
    camera_cf =  z_translate * camera_cf;
    win_refresh(win);
    
}

int main(){
    /* initialize random seed: */
    srand (time(NULL));
    
    if(!glfwInit()) {
        cerr << "Can't initialize GLFW" << endl;
        glfwTerminate();
        exit (EXIT_FAILURE);
    }
    
    glfwSetErrorCallback(err_function);
    GLFWwindow * win;
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    win = glfwCreateWindow(100, 50, "CIS 367 Project 2 -- Tank", NULL, NULL);
    if (!win) {
        cerr << "Can't create window" << endl;
        exit (EXIT_FAILURE);
    }
    
    glfwSetWindowRefreshCallback(win, win_refresh);
    /* On Mac with Retina display there is a discrepancy between units measured in
     * "screen coordinates" and "pixels" */
    glfwSetWindowSizeCallback(win, win_resize);  /* use this for non-retina displays */
    //glfwSetFramebufferSizeCallback(win, win_resize); /* use this for retina displays */
    glfwSetKeyCallback(win, key_handler);
    glfwSetCursorPosCallback(win, cursor_handler);
    glfwSetScrollCallback(win, scroll_handler);
    glfwMakeContextCurrent(win);
    
    /* glewInit must be invoked AFTER glfwMakeContextCurrent() */
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf (stderr, "GLEW init error %s\n", glewGetErrorString(err));
        exit (EXIT_FAILURE);
    }
    
    /* GL functions can be called, only AFTER the window is created */
    const GLubyte *version = glGetString (GL_VERSION);
    printf ("GL Version is %s\n", version);
    
    
    glfwSetWindowSize(win, 800, 600);
    glfwSwapInterval(1);
    init_gl();
    make_model();
    
    win_refresh(win);
    
    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        timer = Timer();
        win_refresh(win);
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    
    return 0;
}

