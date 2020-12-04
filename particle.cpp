#include "Particle.h"

Particle::Particle(const Vector3& position, const Vector3& direction, float speed, const Vector3& color)
{
	mStartPostion = position;
	mCurrentPosition = mStartPostion;
	mTransDirection = direction;
	particleTransSpeed = speed;
	mParticleColor = color;
}

void Particle::InitParticle()
{
	mCurrentPosition = mStartPostion;

	mCurrentPosition.y = 180;
}

void Particle::Update()
{
	mCurrentPosition = mCurrentPosition + mTransDirection * particleTransSpeed;
	if (mCurrentPosition.y < -100)
	{
		InitParticle();
	}
}

void Particle::SetPosition(const Vector3& position)
{
	mStartPostion = position;
	mCurrentPosition = mStartPostion;
}

void Particle::Draw()
{
	glPushMatrix();
	glTranslatef(mCurrentPosition.x, mCurrentPosition.y, mCurrentPosition.z);
	glutSolidCube(0.5f);
	glPopMatrix();
}

void Particle::DisableLightTexture()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Particle::EnableLightTexture()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}
