#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>
#include <QGLWidget>
#include <QTimer>
#include <GLUquadricCylinder.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include "Game.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QTimer timer;
    GLUquadricCylinder cyl;
    Cube cube;
    glm::mat4 camera_cf,light1_cf, light0_cf;

    Game model;

};

#endif // GLWIDGET_H
