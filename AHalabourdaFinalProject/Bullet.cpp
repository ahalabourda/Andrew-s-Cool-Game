#pragma once
#include "raylib.h"
#include "Bullet.h"
#include <math.h>
#include <iostream>

Texture2D Bullet::mSprites[5];

void Bullet::Activate(Vector2 pSpawnPosition, float pSpawnRotation, int pDamageLevel)
{
	mIsActive = true;
	mPosition = pSpawnPosition;
	mRotation = pSpawnRotation;
	mTimerBegin = std::chrono::steady_clock::now();

	// damage levels are 1 indexed so we decrement
	mActiveSprite = &mSprites[pDamageLevel - 1];

}

void Bullet::Deactivate()
{
	mIsActive = false;
}

void Bullet::Draw() const
{

	Rectangle src = Rectangle{ 0, 0, static_cast<float>(mActiveSprite->width), static_cast<float>(mActiveSprite->height) };
	Rectangle dest = Rectangle{ mPosition.x, mPosition.y, static_cast<float>(mActiveSprite->width), static_cast<float>(mActiveSprite->height) };
	
	Vector2 origin = Vector2{ static_cast<float>(mActiveSprite->width / 2), static_cast<float>(mActiveSprite->height / 2) };

	DrawTexturePro(*mActiveSprite, src, dest, origin, mRotation * (180 / PI), WHITE );
	
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

void Bullet::InitializeSprites()
{

	Bullet::mSprites[0] = LoadTexture("art/bullet1.png");
	Bullet::mSprites[1] = LoadTexture("art/bullet2.png");
	Bullet::mSprites[2] = LoadTexture("art/bullet3.png");
	Bullet::mSprites[3] = LoadTexture("art/bullet4.png");
	Bullet::mSprites[4] = LoadTexture("art/bullet5.png");

}
