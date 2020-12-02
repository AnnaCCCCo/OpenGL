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
	void InitParticle();    //  初始化粒子当前位置，初始化为初始位置
	void Update();          //  粒子按移动方向更新坐标
	void SetPosition(const Vector3& position);     //  设置起始位置

	void Draw();

	static void DisableLightTexture();
	static void EnableLightTexture();

private:
	float particleTransSpeed;    // 粒子移动速度
	Vector3 mStartPostion;       // 粒子初始位置
	Vector3 mCurrentPosition;    // 粒子当前位置
	Vector3 mTransDirection;     // 粒子移动方向
	Vector3 mParticleColor;
};
