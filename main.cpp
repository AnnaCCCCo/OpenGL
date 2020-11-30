#include<iostream>
#include<gl/glut.h>
#include<gl/glu.h>
#include<gl/gl.h>

#include "Camera.h"
#include "SkyBox.h"
#include "model.h"
using namespace std;

Camera m_Camera;
CSkyBox m_SkyBox;
CModel m_model;

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
        0.0, 0.0, 0.0, 
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0
    );

    m_model.Init();
}

void drawBuildings() {
    glColor4ub(40, 230, 83, 255);
    m_model.DrawBuilding(Vector3(0, -100, 0), 200.0f, 60.0f, 60.0f);
    m_model.DrawBuilding(Vector3(-10, -100, 70), 100.0f, 40.0f, 80.0f);
    m_model.DrawBuilding(Vector3(10, -100, 200), 200.0f, 80.0f, 100.0f);
    m_model.DrawBuilding(Vector3(10, 100, 200), 40.0f, 50.0f, 80.0f);
    m_model.DrawBuilding(Vector3(180, -100, 0), 200.0f, 80.0f, 60.0f);
    m_model.DrawBuilding(Vector3(180, -100, 60), 250.0f, 80.0f, 60.0f);
    m_model.DrawBuilding(Vector3(210, -100, 200), 250.0f, 100.0f, 100.0f);
    m_model.DrawBuilding(Vector3(360, -100, 30), 150.0f, 80.0f, 120.0f);
    m_model.DrawBuilding(Vector3(360, 50, 30), 100.0f, 40.0f, 100.0f);
    m_model.DrawBuilding(Vector3(370, -100, 180), 200.0f, 60.0f, 100.0f);
    m_model.DrawBuilding(Vector3(420, -100, 10), 130.0f, 40.0f, 80.0f);
    m_model.DrawBuilding(Vector3(540, -100, 0), 200.0f, 80.0f, 60.0f);
    m_model.DrawBuilding(Vector3(540, -100, 170), 150.0f, 80.0f, 80.0f);

    glColor4ub(255, 0, 0, 200);
    m_model.DrawBuilding(Vector3(-10, -100, 290), 200.0f, 40.0f, 80.0f);
    m_model.DrawBuilding(Vector3(10, -100, 380), 250.0f, 80.0f, 60.0f);
    m_model.DrawBuilding(Vector3(10, 150, 380), 50.0f, 60.0f, 20.0f);
    m_model.DrawBuilding(Vector3(0, -100, 440), 200.0f, 60.0f, 60.0f);
    m_model.DrawBuilding(Vector3(10, -100, 500), 150.0f, 80.0f, 60.0f);
    m_model.DrawBuilding(Vector3(190, -100, 290), 150.0f, 60.0f, 80.0f);
    m_model.DrawBuilding(Vector3(210, -100, 410), 200.0f, 60.0f, 80.0f);
    m_model.DrawBuilding(Vector3(210, 100, 410), 30.0f, 40.0f, 60.0f);
    m_model.DrawBuilding(Vector3(230, -100, 490), 100.0f, 100.0f, 80.0f);
    m_model.DrawBuilding(Vector3(230, 0, 490), 150.0f, 80.0f, 60.0f);
    m_model.DrawBuilding(Vector3(390, -100, 280), 170.0f, 100.0f, 100.0f);
    m_model.DrawBuilding(Vector3(380, -100, 400), 100.0f, 40.0f, 60.0f);
    m_model.DrawBuilding(Vector3(410, -100, 450), 150.0f, 100.0f, 40.0f);
    m_model.DrawBuilding(Vector3(410, -100, 510), 150.0f, 60.0f, 40.0f);
    m_model.DrawBuilding(Vector3(560, -100, 270), 250.0f, 40.0f, 120.0f);
    m_model.DrawBuilding(Vector3(550, -100, 450), 150.0f, 60.0f, 160.0f);
    m_model.DrawBuilding(Vector3(550, 50, 450), 100.0f, 30.0f, 100.0f);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    m_Camera.setLook();
    //m_SkyBox.CreateSkyBox(m_Camera.getPosition());
    drawBuildings();
    glFlush();
    glutPostRedisplay();
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
        m_Camera.movement(true, 10.0f, GLUT_KEY_F1);
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
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutPassiveMotionFunc(motion);
    glutMainLoop();
    return 0;
}