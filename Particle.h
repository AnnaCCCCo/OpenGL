#pragma once
#pragma once

#include<GL/glut.h>
#include"vector.h"

class Particle
{
public:
	explicit Particle(const Vector3& position, const Vector3& direction, float speed, const Vector3& color = Vector3(0.9, 0.9, 1.0));
	explicit Particle()
	{
		particleTransSpeed = 1.0;
		mStartPostion = Vector3();
		mCurrentPosition = Vector3();
		mTransDirection = Vector3(0.2, -1.0, 0.0);
		mParticleColor = Vector3(0.8, 0.8, 1.0);
	}
	void InitParticle();    //  ��ʼ�����ӵ�ǰλ�ã���ʼ��Ϊ��ʼλ��
	void Update();          //  ���Ӱ��ƶ������������
	void SetPosition(const Vector3& position);     //  ������ʼλ��

	void Draw();

	static void DisableLightTexture();
	static void EnableLightTexture();

private:
	float particleTransSpeed;    // �����ƶ��ٶ�
	Vector3 mStartPostion;       // ���ӳ�ʼλ��
	Vector3 mCurrentPosition;    // ���ӵ�ǰλ��
	Vector3 mTransDirection;     // �����ƶ�����
	Vector3 mParticleColor;
};
