#include "Enemy.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>

const float Enemy::size = 20.0f;
const float Enemy::growthRate = 1.1f;
const Color Enemy::colour{ 200, 30, 30, 255 };
const float Enemy::speed = 2.0f;

Enemy::Enemy()
{

}

void Enemy::Tick(const Vector2 & target)
{
	
	// 
	float deltaX = (target.x - (size /2)) - position.x;
	float deltaY = (target.y - (size / 2)) - position.y;

	float distance = sqrtf((deltaX) * (deltaX) + (deltaY) * (deltaY));

	if (distance > speed) {

		float ratio = speed / distance;

		position.x += ratio * deltaX;
		position.y += ratio * deltaY;

	}
	else {
		position.x = target.x - (size / 2);
		position.y = target.y - (size / 2);
	}

	rect.x = position.x;
	rect.y = position.y;

	rect.width = size * growthRate * (GetAgeInMilliseconds() * .001f);
	rect.height = size * growthRate * (GetAgeInMilliseconds() * .001f);

}

void Enemy::Draw() const
{

	//DrawTriangle(Vector2{ position.x, position.y + 1 }, Vector2{ position.x - 1, position.y }, Vector2{ position.x + 1, position.y }, colour);

	DrawRectangleRec(rect, colour);

}

void Enemy::Activate()
{

	begin = std::chrono::steady_clock::now();
	PlaceRandomly();

	isActive = true;

}

void Enemy::Deactivate()
{
	isActive = false;
}

void Enemy::PlaceRandomly()
{
	
	int side = rand() % 4;

	switch (side) {
		case 0: // left of screen
			position.x = -10.0f;
			position.y = (float)(rand() % GetScreenHeight());
			break;
		case 1: // right of screen
			position.x = GetScreenWidth() + 10.0f;
			position.y = (float)(rand() % GetScreenHeight());
			break;
		case 2: // above screen
			position.x = (float)(rand() % GetScreenWidth());
			position.y = -10.0f;
			break;
		case 3: // below screen
			position.x = (float)(rand() % GetScreenWidth());
			position.y = GetScreenHeight() + 10.0f;
			break;
	}

}

int Enemy::GetAgeInMilliseconds() const {
	
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count();

}