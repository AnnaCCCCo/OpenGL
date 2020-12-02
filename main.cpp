#include<iostream>
#include<gl/glut.h>
#include<gl/glu.h>
#include<gl/gl.h>
#include<random>

#include "Camera.h"
#include "SkyBox.h"
#include "model.h"
#include "Particle.h"
using namespace std;

Camera m_Camera;
CSkyBox m_SkyBox;
CModel m_model;
Particle* particles;
CBMPLoader groundTex;

const unsigned int particleNum = 4000;

float RandX()          //random particle x range from -130 to 680
{
    return (rand() % 810) - 130;
}
float RandY()          //random particle y range from -100 to 300
{
    return (rand() % 400) - 100;
}
float RandZ()          //random particle z range from -130 to 630
{
    return (rand() % 760) - 130;
}

void drawGround() {
    float ambientMaterial[] = { 0.3, 0.3, 0.3, 1.0 };
    float diffuseMaterial[] = { 0.8, 0.8, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMaterial);

    glBindTexture(GL_TEXTURE_2D, groundTex.ID);
    glBegin(GL_QUADS);
    
    glNormal3f(0, 1, 0);


    glTexCoord2f(0.0f, 0.0f); glVertex3f(-130, -100, -130);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-130, -100, 630);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(680, -100, 630);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(680, -100, -130);
    glEnd();
}

void groundInit() {
    char* filename = "ground.bmp";
    if (!groundTex.LoadBitmap(filename)) {
        exit(0);
    }
    glGenTextures(1, &groundTex.ID);
    glBindTexture(GL_TEXTURE_2D, groundTex.ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_FILL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_FILL);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, groundTex.imageWidth,
        groundTex.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
        groundTex.image);

}

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_TEXTURE_2D);

    //   粒子初始化位置
    particles = new Particle[particleNum];
    Vector3 position;
    for (int i = 0; i < particleNum; ++i)
    {
        position = Vector3(RandX(), RandY(), RandZ());
        particles[i].SetPosition(position);
    }

    //skybox
    if (!m_SkyBox.Init("back", "front", "bottom", "top", "right", "left"))
    {
        exit(0);
    }

    //camera
    m_Camera.setCamera(
        79.0f, 0.0f, -38.0f, 
        79.0f, 0.0f, -37.0f, 
        0.0f, 1.0f, 0.0f
    );

    groundInit();
    m_model.Init();

    ///*
    glEnable(GL_LIGHTING);

    float ambientColor[] = { 0.3, 0.3, 0.3, 1.0 };   
    float diffuseColor[] = { 0.8, 0.8, 0.8, 1.0 };   
    float specularColor[] = { 1.0, 1.0, 1.0, 1.0 };  
    float lightPos[] = { -130.0, 300.0, -130.0, 0.0 };//the position of light. the last 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);
    //*/
}

void drawBuildings() {
    float ambientMaterial[] = { 0.3, 0.3, 0.3, 1.0 };
    float diffuseMaterial[] = { 0.8, 0.8, 0.8, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMaterial);

    glColor4ub(123, 211, 185, 50);
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

    glColor4ub(211, 123, 169, 50);
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
    
    m_SkyBox.CreateSkyBox(m_Camera.getPosition());
    drawGround();
    drawBuildings();
    
    // Particle
    Particle::DisableLightTexture();
    glColor3f(0.8, 0.8, 1.0);
    for (int i = 0; i < particleNum; ++i)
    {
        particles[i].Draw();
        particles[i].Update();
    }
    Particle::EnableLightTexture();

    glFlush();
    glutPostRedisplay();
}

void ChangeSize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 0.1f, 4000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void motion(int x, int y) {
    m_Camera.setViewByMouse();
    cout << "VIEW: " << m_Camera.getVX() << "  " << m_Camera.getVY() << "  " << m_Camera.getVZ() << endl;
    cout << "UP: " << m_Camera.getUX() << "  " << m_Camera.getUY() << "  " << m_Camera.getUZ() << endl;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    bool autoCamera = false;
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
        cout << m_Camera.getX() << "  " << m_Camera.getY() << "  " << m_Camera.getZ() << endl;
        break;
    case 's':
        m_Camera.movement(false, -m_Camera.getSpeed(), 's');
        cout << m_Camera.getX() << "  " << m_Camera.getY() << "  " << m_Camera.getZ() << endl;
        break;
    case 'a':
        m_Camera.movement(false, -m_Camera.getSpeed(), 'a');
        cout << m_Camera.getX() << "  " << m_Camera.getY() << "  " << m_Camera.getZ() << endl;
        break;
    case 'd':
        m_Camera.movement(false, m_Camera.getSpeed(), 'd');
        cout << m_Camera.getX() << "  " << m_Camera.getY() << "  " << m_Camera.getZ() << endl;
        break;
    case GLUT_KEY_F1:
        if (autoCamera == false) {
            autoCamera = true;
        }
        else {
            autoCamera = false;
        }
        break;
    default:
        m_Camera.movement(autoCamera, 10.0f, GLUT_KEY_F1);
        break;
    }

    glutPostRedisplay();
}

void keychart() {
    cout << "Use ESC to exit." << endl
        << "Use WASD to move the camera." << endl
        << "Press F1 to activate/de-activate auto camera." << endl;
}

int main(int argc, char** argv) {
    keychart();
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
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glutMainLoop();
    return 0;
}