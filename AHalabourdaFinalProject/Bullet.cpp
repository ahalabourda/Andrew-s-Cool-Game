#pragma once

#include "Bullet.h"
#include <math.h>

const float Bullet::size = 3.0f;
const float Bullet::damage = 5.0f;
const float Bullet::speed = 10.0f;

Bullet::Bullet()
{
	
}

void Bullet::Activate(Vector2 spawnPosition, float spawnRotation)
{
	isActive = true;
	position = spawnPosition;
	rotation = spawnRotation;
	begin = std::chrono::steady_clock::now();
}

void Bullet::Deactivate()
{
	isActive = false;
}

void Bullet::Draw() const
{
	DrawCircleV(position, size, colour);
}

void Bullet::Tick()
{
	if (isActive) {

		position.x += speed * cosf(rotation);
		position.y += speed * sinf(rotation);

		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() >= lifespanInMilliseconds) {

			isActive = false;

		}
		
	}

}