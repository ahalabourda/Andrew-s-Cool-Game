#include "Player.h"
#include <algorithm>

Player::Player(float startX, float startY)
	: position(Vector2{ startX, startX })
{
}

void Player::Move(float movementX, float movementY)
{

	position.x = std::clamp(position.x + (movementX * speed), 0.0f, (float)GetScreenWidth());
	position.y = std::clamp(position.y + (movementY * speed), 0.0f, (float)GetScreenHeight());

	

}

void Player::Draw() const
{

	DrawCircleV(position, size, colour);

}