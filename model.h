#pragma once
#ifndef __MODEL_H__
#define __MODEL_H__

#include <iostream>
#include "CBMPLoader.h"
#include "Vector.h"
#include <windows.h>
#include <gl/glu.h>

class CModel {
private:
	float x;
	float y;
	float z;
	Vector3 position;
	CBMPLoader texture;
	const float perwindow = 5.0f;

public:
	void DrawBuilding(Vector3 pos, float height, float length, float width);
	void Init();
};

#endif //__MODEL_H__
