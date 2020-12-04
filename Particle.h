#pragma once
#pragma once

#include<GL/glut.h>
#include"vector.h"

class Particle
{
private:
	float particleTransSpeed;
	Vector3 mStartPostion;
	Vector3 mCurrentPosition;
	Vector3 mTransDirection;
	Vector3 mParticleColor;
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
	void InitParticle();
	void Update();
	void SetPosition(const Vector3& position);

	void Draw();

	static void DisableLightTexture();
	static void EnableLightTexture();
};
