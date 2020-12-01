#include <iostream>
#include "model.h"
#include <time.h>
using namespace std;

int randmap = 0;

void CModel::DrawBuilding(Vector3 pos, float height, float length, float width) {
	x = pos.x;
	y = pos.y;
	z = pos.z;

	float yWindow = height / perwindow;
	float yTexPos = yWindow / 64;

	float xLWindow = length / perwindow;
	float xLTexPos = xLWindow / 64;

	float xWWindow = width / perwindow;
	float xWTexPos = xWWindow / 64;

	float halfL = length / 2;
	float halfW = width / 2;

	glPushMatrix();

	//bottom
	glBegin(GL_QUADS);
	glVertex3f(x + halfL, y, z + halfW);
	glVertex3f(x - halfL, y, z + halfW);
	glVertex3f(x - halfL, y, z - halfW);
	glVertex3f(x + halfL, y, z - halfW);
	glEnd();

	//top
	glBegin(GL_QUADS);
	glVertex3f(x + halfL, y + height, z + halfW);
	glVertex3f(x - halfL, y + height, z + halfW);
	glVertex3f(x - halfL, y + height, z - halfW);
	glVertex3f(x + halfL, y + height, z - halfW);
	glEnd();

	//round-----------------------------------
	srand((unsigned)time(NULL));
	randmap = rand() % 5;
	glBindTexture(GL_TEXTURE_2D, texture[randmap].ID);
	glBegin(GL_QUADS);
	glTexCoord2f(xLTexPos, 0.0f); glVertex3f(x + halfL, y, z + halfW);                //right down
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x - halfL, y, z + halfW);                    //left down
	glTexCoord2f(0.0f, yTexPos); glVertex3f(x - halfL, y + height, z + halfW);        //left up
	glTexCoord2f(xLTexPos, yTexPos); glVertex3f(x + halfL, y + height, z + halfW);    //right up
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(xLTexPos, 0.0f); glVertex3f(x + halfL, y, z + halfW);                       //left down
	glTexCoord2f(xLTexPos + xWTexPos, 0.0f); glVertex3f(x + halfL, y, z - halfW);            //right down
	glTexCoord2f(xLTexPos + xWTexPos, yTexPos); glVertex3f(x + halfL, y + height, z - halfW);//right up
	glTexCoord2f(xLTexPos, yTexPos); glVertex3f(x + halfL, y + height, z + halfW);           //left up
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(xLTexPos + xWTexPos, 0.0f); glVertex3f(x + halfL, y, z - halfW);                //left down
	glTexCoord2f(2 * xLTexPos + xWTexPos, 0.0f); glVertex3f(x - halfL, y, z - halfW);            //right down
	glTexCoord2f(2 * xLTexPos + xWTexPos, yTexPos); glVertex3f(x - halfL, y + height, z - halfW);//right up
	glTexCoord2f(xLTexPos + xWTexPos, yTexPos); glVertex3f(x + halfL, y + height, z - halfW);    //left up
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(2 * xLTexPos + 2 * xWTexPos, 0.0f); glVertex3f(x - halfL, y, z + halfW);            //right down
	glTexCoord2f(2 * xLTexPos + xWTexPos, 0.0f); glVertex3f(x - halfL, y, z - halfW);                //left down
	glTexCoord2f(2 * xLTexPos + xWTexPos, yTexPos); glVertex3f(x - halfL, y + height, z - halfW);    //left up
	glTexCoord2f(2 * xLTexPos + 2 * xWTexPos, yTexPos); glVertex3f(x - halfL, y + height, z + halfW);//right up
	glEnd();

	glPopMatrix();
}

void CModel::Init() {
	char* filename;
	char* bmpName[] = { "city.bmp","city2.bmp","city3.bmp","city4.bmp","city5.bmp" };
	for (int i = 0; i < 5; i++) {
		filename = bmpName[i];
		if (!texture[i].LoadBitmap(filename)) {
			exit(0);
		}
		glGenTextures(1, &texture[i].ID);
		glBindTexture(GL_TEXTURE_2D, texture[i].ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_FILL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_FILL);

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texture[i].imageWidth,
			texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
			texture[i].image);
	}
}