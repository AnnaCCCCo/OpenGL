#include <iostream>
#include "Camera.h"
#include <time.h>
using namespace std;

Camera::Camera() {
    Vector3 zero = Vector3(0.0, 0.0, 0.0);
    Vector3 view = Vector3(0.0, 0.0, 1.0);
    Vector3 up = Vector3(0.0, 1.0, 0.0);

    m_Position = zero;
    m_View = view;
    m_UpVector = up;
    m_Speed = 10.0f;
}

void Camera::setCamera(
    float positionX, float positionY, float positionZ, //position
    float viewX, float viewY, float viewZ,             //view direction
    float upVectorX, float upVectorY, float upVectorZ) //normal
{
    Vector3 Position = Vector3(positionX, positionY, positionZ);
    Vector3 View = Vector3(viewX, viewY, viewZ);
    Vector3 UpVector = Vector3(upVectorX, upVectorY, upVectorZ);

    m_Position = Position;
    m_View = View;
    m_UpVector = UpVector;
}

void Camera::rotateView(float angle, float x, float y, float z) {
    Vector3 view = m_View - m_Position;
    Vector3 newView;
    
    float cosTheta = (float)cos(angle);
    float sinTheta = (float)sin(angle);

    //calculate x
    newView.x = (cosTheta + (1 - cosTheta) * x * x) * view.x;
    newView.x += ((1 - cosTheta) * x * y - z * sinTheta) * view.y;
    newView.x += ((1 - cosTheta) * x * z + y * sinTheta) * view.z;

    //calculate y
    newView.y = ((1 - cosTheta) * x * y + z * sinTheta) * view.x;
    newView.y += (cosTheta + (1 - cosTheta) * y * y) * view.y;
    newView.y += ((1 - cosTheta) * y * z - x * sinTheta) * view.z;

    //calculate z
    newView.z = ((1 - cosTheta) * x * z - y * sinTheta) * view.x;
    newView.z += ((1 - cosTheta) * y * z + x * sinTheta) * view.y;
    newView.z += (cosTheta + (1 - cosTheta) * z * z) * view.z;

    //update the rotation of camera
    m_View = m_Position + newView;
}

void Camera::setViewByMouse() {//rotate the camera by mouse
    POINT mousePos;                                   //mouse position right now
    int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1; //half the length of screen
    int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1; //half the width
    float angleY = 0.0f;                              //angle left to right
    float angleZ = 0.0f;                              //angle up to down
    static float currentRotX = 0.0f;

    GetCursorPos(&mousePos);
    ShowCursor(FALSE);

    if ((mousePos.x == middleX) && (mousePos.y == middleY)) {
        return;
    }

    SetCursorPos(middleX, middleY);

    angleY = (float)((middleX - mousePos.x)) / 1000.0f;
    angleZ = (float)((middleY - mousePos.y)) / 1000.0f;

    static float lastRotX = 0.0f;//angle
    
    lastRotX = currentRotX;
    currentRotX += angleZ;

    if (currentRotX > 1.0f) {
        currentRotX = 1.0f;
        if (lastRotX != 1.0f) {
            //通过叉积找到与旋转方向垂直的向量
            Vector3 vAxis = m_View - m_Position;
            vAxis = vAxis.crossProduct(m_UpVector);
            vAxis = vAxis.normalize();

            rotateView(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
        }
    }
    else if (currentRotX < -1.0f) {
        currentRotX = -1.0f;
        if (lastRotX != -1.0f) {
            //通过叉积找到与旋转方向垂直的向量
            Vector3 vAxis = m_View - m_Position;
            vAxis = vAxis.crossProduct(m_UpVector);
            vAxis = vAxis.normalize();

            rotateView(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
        }
    }
    else {//angle z
        Vector3 vAxis = m_View - m_Position;
        vAxis = vAxis.crossProduct(m_UpVector);
        vAxis = vAxis.normalize();

        rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
    }
    rotateView(angleY, 0, 1, 0);
}

void Camera::yawCamera(float speed) {
    Vector3 yaw;
    Vector3 cross = m_View - m_Position;
    cross = cross.crossProduct(m_UpVector);

    // Normalize the strafe vector
    yaw = cross.normalize();

    m_Position.x += yaw.x * speed;
    m_Position.z += yaw.z * speed;

    // Add the strafe vector to our view
    m_View.x += yaw.x * speed;
    m_View.z += yaw.z * speed;
}

void Camera::moveCamera(float speed) {
    Vector3 vector = m_View - m_Position;
    vector = vector.normalize();

    //update camera
    m_Position.x += vector.x * speed;
    m_Position.z += vector.z * speed;
    m_View.x += vector.x * speed;
    m_View.z += vector.z * speed;
}

void Camera::setLook() {
    gluLookAt(m_Position.x, m_Position.y, m_Position.z,
        m_View.x, m_View.y, m_View.z,
        m_UpVector.x, m_UpVector.y, m_UpVector.z);
}

void Camera::movement(bool autoCamera, float speed, char key) {
    if (autoCamera) {
        autoMove();
    }
    else {
        switch (key) {
        case 'w':
            moveCamera(speed);
            break;
        case 's':
            moveCamera(speed);
            break;
        case 'a':
            yawCamera(speed);
            break;
        case 'd':
            yawCamera(speed);
            break;
        }
    }
}

int getTime()
{
    return clock() / CLOCKS_PER_SEC;
}

int lastTime = 0;

void Camera::autoMove() {
    gluLookAt(79.0f, 0.0f, -38.0f,
        79.0f, 0.0f, -37.0f,
        0.0f, 1.0f, 0.0f);

    int now = getTime();
    if (now - lastTime > 0)
    {
        moveCamera(20.0f);
        lastTime = now;
    }

}
