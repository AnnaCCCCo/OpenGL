#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <windows.h>
#include <gl/glu.h>
#include "Vector.h"

class Camera
{
private:
    Vector3        m_Position;
    Vector3        m_View;
    Vector3        m_UpVector;
    float          m_Speed;
public:
    Camera();
    Vector3 getPosition() { return m_Position; }
    Vector3 getView() { return m_View; }
    Vector3 getUpVector() { return m_UpVector; }
    float getSpeed() { return m_Speed; }

    void setSpeed(float speed)
    {
        m_Speed = speed;
    }

    void setCamera(
        float positionX, float positionY, float positionZ,
        float viewX, float viewY, float viewZ,
        float upVectorX, float upVectorY, float upVectorZ);
    void rotateView(float angle, float X, float Y, float Z);
    void setViewByMouse();
    void yawCamera(float speed);
    void moveCamera(float speed);
    void movement(bool autoCamera, float speed, char key);

    void setLook();
};

#endif //__CAMERA_H__
