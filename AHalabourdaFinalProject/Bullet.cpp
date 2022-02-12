#pragma once
#include "raylib.h"
#include "Bullet.h"
#include <math.h>



Bullet::Bullet()
{
	
}

void Bullet::Activate(Vector2 spawnPosition, float spawnRotation)
{
	mIsActive = true;
	mPosition = spawnPosition;
	mRotation = spawnRotation;
	mTimerBegin = std::chrono::steady_clock::now();
}

void Bullet::Deactivate()
{
	mIsActive = false;
}

void Bullet::Draw() const
{
	DrawCircleV(mPosition, msSize, msColour);
}

void Bullet::Tick()
{
	if (mIsActive) {

		mPosition.x += msSpeed * cosf(mRotation);
		mPosition.y += msSpeed * sinf(mRotation);

		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mTimerBegin).count() >= msLifespanInMilliseconds) {

			mIsActive = false;

		}
		
	}

}