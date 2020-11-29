#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "SkyBox.h"
using namespace std;

CSkyBox::CSkyBox() {}

CSkyBox::~CSkyBox(){
    for (int i = 0; i < 6; i++)
    {
        m_texture[i].FreeImage();
        glDeleteTextures(1, &m_texture[i].ID);
    }

}

bool CSkyBox::Init(char* back, char* front, char* bottom, char* top, char* right, char* left){
    char filename[128];
    char* bmpName[] = { back,front,bottom,top,right,left };
    for (int i = 0; i < 6; i++)
    {
        sprintf(filename, "%s", bmpName[i]);
        strcat(filename, ".bmp");
        if (!m_texture[i].LoadBitmap(filename))
        {
            exit(0);
        }
        glGenTextures(1, &m_texture[i].ID);

        glBindTexture(GL_TEXTURE_2D, m_texture[i].ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture[i].imageWidth,
            m_texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
            m_texture[i].image);
    }
    return true;

}

void  CSkyBox::CreateSkyBox(
    Vector3 position,
    float box_width, float box_height,
    float box_length) 
{
    GLboolean lp;
    glGetBooleanv(GL_LIGHTING, &lp);

    float width = MAP * box_width / 8;
    float height = MAP * box_height / 8;
    float length = MAP * box_length / 8;

    position.x = position.x + MAP / 8 - width / 2;
    position.y = position.y + MAP / 24 - height / 2;
    position.z = position.z + MAP / 8 - length / 2;

    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(-position.x, -position.y, -position.z);

    //back
    glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);

    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(position.x + width, position.y, position.z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(position.x + width, position.y + height, position.z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(position.x, position.y + height, position.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(position.x, position.y, position.z);

    glEnd();

    //front
    glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);

    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(position.x, position.y, position.z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(position.x, position.y + height, position.z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(position.x + width, position.y + height, position.z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(position.x + width, position.y, position.z + length);

    glEnd();

    //bottom
    glBindTexture(GL_TEXTURE_2D, m_texture[2].ID);

    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(position.x, position.y, position.z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(position.x, position.y, position.z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(position.x + width, position.y, position.z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(position.x + width, position.y, position.z);

    glEnd();

    //top
    glBindTexture(GL_TEXTURE_2D, m_texture[3].ID);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f); glVertex3f(position.x + width, position.y + height, position.z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(position.x + width, position.y + height, position.z + length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(position.x, position.y + height, position.z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(position.x, position.y + height, position.z);

    glEnd();

    //left
    glBindTexture(GL_TEXTURE_2D, m_texture[4].ID);

    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(position.x, position.y + height, position.z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(position.x, position.y + height, position.z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(position.x, position.y, position.z + length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(position.x, position.y, position.z);

    glEnd();

    //right
    glBindTexture(GL_TEXTURE_2D, m_texture[5].ID);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(position.x + width, position.y, position.z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(position.x + width, position.y, position.z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(position.x + width, position.y + height, position.z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(position.x + width, position.y + height, position.z);
    glEnd();

    glPopMatrix();

    if (lp) {
        glEnable(GL_LIGHTING);
    }

}
