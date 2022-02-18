#include "Enemy.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>

void Enemy::Tick(const Vector2 & target)
{
	
	// 
	float deltaX = target.x - mPosition.x;
	float deltaY = target.y - mPosition.y;

	float distance = sqrtf((deltaX) * (deltaX) + (deltaY) * (deltaY));

	if (distance > msSpeed) { // we are more than 1 tick of movement away from the target. move normally

		float ratio = msSpeed / distance;

		mPosition.x += ratio * deltaX;
		mPosition.y += ratio * deltaY;

	}
	else { // we are less than 1 tick of movement away from the target! just teleport there
		mPosition.x = target.x;
		mPosition.y = target.y;
	}

	mRect.x = mPosition.x - mSprite.width * mTextureScale / 2.0f;
	mRect.y = mPosition.y - mSprite.height * mTextureScale / 2.0f;

	//mRect.width = msSize * msGrowthRate * (GetAgeInMilliseconds() * .001f);
	//mRect.height = msSize * msGrowthRate * (GetAgeInMilliseconds() * .001f);

	mRect.width = mSprite.width * mTextureScale;
	mRect.height = mSprite.height * mTextureScale;

	mTextureScale = GetAgeInMilliseconds() * .00005f;

}

void Enemy::Draw() const
{

	//DrawRectangleRec(mRect, GetActualColour());

	DrawTexturePro(	mSprite,
					Rectangle{ 0.0f, 0.0f, static_cast<float>(mSprite.width), static_cast<float>(mSprite.height) },
					Rectangle{ mPosition.x, mPosition.y, static_cast<float>(mSprite.width) * mTextureScale, static_cast<float>(mSprite.height) * mTextureScale },
					Vector2{ static_cast<float>(mSprite.width * mTextureScale / 2), static_cast<float>(mSprite.height * mTextureScale / 2.0f) },
					baseRotation + GetAgeInMilliseconds() * .01f,
					GetActualColour());

}

void Enemy::Activate()
{

	healthCurrent = healthMax;
	mTimerBegin = std::chrono::steady_clock::now();
	PlaceRandomly();

	mIsActive = true;
	baseRotation = rand() * 360.0f;

}

void Enemy::Deactivate()
{
	mIsActive = false;
	mTextureScale = 1.0f;
}

void Enemy::PlaceRandomly()
{
	
	int side = rand() % 4;

	switch (side) {
		case 0: // left of screen
			mPosition.x = -10.0f;
			mPosition.y = static_cast<float>(rand() % GetScreenHeight());
			break;
		case 1: // right of screen
			mPosition.x = GetScreenWidth() + 10.0f;
			mPosition.y = static_cast<float>(rand() % GetScreenHeight());
			break;
		case 2: // above screen
			mPosition.x = static_cast<float>(rand() % GetScreenWidth());
			mPosition.y = -10.0f;
			break;
		case 3: // below screen
			mPosition.x = static_cast<float>(rand() % GetScreenWidth());
			mPosition.y = GetScreenHeight() + 10.0f;
			break;
	}

}

int Enemy::GetAgeInMilliseconds() const {
	
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mTimerBegin).count();

}

bool Enemy::TakeDamage(float pDamage)
{

	healthCurrent -= pDamage;
	if (healthCurrent <= 0.0f) {
		Deactivate();
		return true;
	}
	else {
		return false;
	}

}
