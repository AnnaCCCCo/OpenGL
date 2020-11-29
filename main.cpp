#include<iostream>
#include<gl/glut.h>
#include<gl/glu.h>
#include<gl/gl.h>

#include "Camera.h"
#include "SkyBox.h"

Camera m_Camera;
CSkyBox m_SkyBox;

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_TEXTURE_2D);

    //skybox
    if (!m_SkyBox.Init("back", "front", "bottom", "top", "right", "left"))
    {
        exit(0);
    }

    //camera
    m_Camera.setCamera(
        500, 35, 400, 
        501, 35, 400, 
        0, 1, 0
    );
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    m_Camera.setLook();
    m_SkyBox.CreateSkyBox(m_Camera.getPosition(), 1.0, 0.5, 1.0);

    glFlush();
}

void ChangeSize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 4000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void motion(int x, int y) {
    m_Camera.setViewByMouse();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    case '1':
        m_Camera.setSpeed(1.0f);
        break;
    case '2':
        m_Camera.setSpeed(10.0f);
        break;
    case 'w':
        m_Camera.movement(false, m_Camera.getSpeed(), 'w');
        break;
    case 's':
        m_Camera.movement(false, -m_Camera.getSpeed(), 's');
        break;
    case 'a':
        m_Camera.movement(false, -m_Camera.getSpeed(), 'a');
        break;
    case 'd':
        m_Camera.movement(false, m_Camera.getSpeed(), 'd');
        break;
    case GLUT_KEY_F1:
        m_Camera.movement(true, 15.0f, GLUT_KEY_F1);
        break;
    }

    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);

    //window size and position
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0,0);
    glutCreateWindow("demo");

    init();

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(display);
    glutPassiveMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}