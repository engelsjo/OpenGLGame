#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){ //init model method
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    //set up lighting
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    //set the camera
    /* place the camera at Z=+5 (notice that the sign is OPPOSITE!) */
    //camera_cf = glm::translate(glm::vec3{-20, 20, -20}) * camera_cf;
    camera_cf = glm::rotate(glm::radians(-45.0f), glm::vec3{0, 0, 1}) * camera_cf;
    camera_cf = glm::rotate(glm::radians(-45.0f), glm::vec3{1, 0, 0}) * camera_cf;
    camera_cf = glm::scale(glm::vec3 {.02,.02,.02}) * camera_cf;


    cyl.build();
}

void GLWidget::paintGL(){ //think of this method as win-refresh
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    /* place the camera using the camera coordinate frame */
    glMultMatrixf (glm::value_ptr(camera_cf));

    glRotatef(.5, 1, 1, 1);
    cyl.render();
}

void GLWidget::resizeGL(int w, int h){ //handle resizing window
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w/h, 1, 10);
}
