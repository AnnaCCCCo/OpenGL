#pragma once

#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include <iostream>
#include "CBMPLoader.h"
#include "Vector.h"
#include "Camera.h"

#define GL_CLAMP_TO_EDGE    0x812F

class CSkyBox
{
private:
    CBMPLoader  m_texture[6];
public:
    CSkyBox();
    ~CSkyBox();

    float x;
    float y;
    float z;

    bool Init(char* back, char* front, char* bottom, char* top, char* right, char* left);

    void CreateSkyBox(Vector3 position);
    const unsigned int MAP_WIDTH = 2048;
    const unsigned int CELL_WIDTH = 16;
    const unsigned int MAP = MAP_WIDTH * CELL_WIDTH / 2;
};
#endif ///__SKYBOX_H__
