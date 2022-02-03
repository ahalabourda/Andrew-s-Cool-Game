#include "Player.h"

Player::Player(float startX, float startY)
	: position(Vector2{ startX, startX })
{
}

void Player::Move(float movementX, float movementY)
{

	position.x += movementX * speed;
	position.y += movementY * speed;

}

void Player::Draw() const
{

	DrawCircleV(position, size, colour);

}