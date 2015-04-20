#include "glwidget.h"

GLfloat light0_color [] = {1.0, 1.0, 1.0, 1.0};
GLfloat light1_color [] = {1.0, 1.0, 0.8, 1.0};
GLfloat black_color [] = {0.0, 0.0, 0.0, 1.0};

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){ //init model method

    //glClearColor(0, 0, 0, 0);
    //glEnable(GL_DEPTH_TEST);

    glewInit();

    //set up lighting
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);

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


    //set the camera
    /* place the camera at Z=+5 (notice that the sign is OPPOSITE!) */
    camera_cf = glm::translate(glm::vec3{0, 275, -175}) * camera_cf;
    //camera_cf = glm::rotate(glm::radians(-45.0f), glm::vec3{0, 0, 1}) * camera_cf;
    camera_cf = glm::rotate(glm::radians(-60.0f), glm::vec3{1, 0, 0}) * camera_cf;
    camera_cf = glm::scale(glm::vec3 {.02,.02,.02}) * camera_cf;


    model.init();
}

void GLWidget::paintGL(){ //think of this method as win-refresh
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* place the camera using the camera coordinate frame */
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
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

    auto objects = model.get_objects();
    if (objects.size() != 0){
        Football* football = (Football*)objects[0].first;
        Upright* upright = (Upright*)objects[1].first;
        Bleachers* bleacher = (Bleachers*)objects[2].first;
        Bleachers* bleacher1 = (Bleachers*)objects[3].first;
        Upright* upright1 = (Upright*)objects[4].first;

        //coord frames
        glm::mat4x4 mat1 = objects[0].second;
        glm::mat4x4 mat2 = objects[1].second;
        glm::mat4x4 mat3 = objects[2].second;
        glm::mat4x4 mat4 = objects[3].second;
        glm::mat4x4 mat5 = objects[4].second;

        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mat1));
        (*football).render(false);
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
}

void GLWidget::resizeGL(int w, int h){ //handle resizing window
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, .1, 100);
}

