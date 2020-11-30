#include <iostream>
#include "model.h"
using namespace std;

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
	glBindTexture(GL_TEXTURE_2D, texture.ID);
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
	char filename[] = "city.bmp";
	if (!texture.LoadBitmap(filename)) {
		exit(0);
	}
	glGenTextures(1, &texture.ID);
	glBindTexture(GL_TEXTURE_2D, texture.ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_FILL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_FILL);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texture.imageWidth,
		texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		texture.image);
}