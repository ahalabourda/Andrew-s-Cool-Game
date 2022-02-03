#pragma once

#include "Bullet.h"
#include <math.h>

Bullet::Bullet()
{
}

void Bullet::Activate(Vector2 spawnPosition, float spawnRotation)
{
	DrawText("activating a bullet!", 290, 350, 20, BLACK);
	isActive = true;
	position = spawnPosition;
	rotation = spawnRotation;
	begin = std::chrono::steady_clock::now();
}

void Bullet::Draw() const
{
	DrawText("drawing a bullet!", 290, 250, 20, BLACK);
	DrawCircleV(position, size, colour);
}

void Bullet::Tick()
{
	if (isActive) {
		DrawText("ticking a bullet!", 290, 300, 20, BLACK);

		position.x += speed * cos(rotation);
		position.y += speed * sin(rotation);

		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() >= lifespanInMilliseconds) {

			isActive = false;

		}
		
	}

}