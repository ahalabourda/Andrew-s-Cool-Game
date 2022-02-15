#include "Enemy.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>

Enemy::Enemy()
{

}

void Enemy::Tick(const Vector2 & target)
{
	
	// 
	float deltaX = (target.x - (msSize /2)) - mPosition.x;
	float deltaY = (target.y - (msSize / 2)) - mPosition.y;

	float distance = sqrtf((deltaX) * (deltaX) + (deltaY) * (deltaY));

	if (distance > msSpeed) {

		float ratio = msSpeed / distance;

		mPosition.x += ratio * deltaX;
		mPosition.y += ratio * deltaY;

	}
	else {
		mPosition.x = target.x - (msSize / 2);
		mPosition.y = target.y - (msSize / 2);
	}

	mRect.x = mPosition.x;
	mRect.y = mPosition.y;

	mRect.width = msSize * msGrowthRate * (GetAgeInMilliseconds() * .001f);
	mRect.height = msSize * msGrowthRate * (GetAgeInMilliseconds() * .001f);

}

void Enemy::Draw() const
{

	//DrawTriangle(Vector2{ position.x, position.y + 1 }, Vector2{ position.x - 1, position.y }, Vector2{ position.x + 1, position.y }, colour);

	DrawRectangleRec(mRect, GetActualColour());

}

void Enemy::Activate()
{

	healthCurrent = healthMax;
	mTimerBegin = std::chrono::steady_clock::now();
	PlaceRandomly();

	mIsActive = true;

}

void Enemy::Deactivate()
{
	mIsActive = false;
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
