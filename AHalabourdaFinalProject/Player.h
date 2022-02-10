#pragma once
#include <raylib.h>
#include <Upgrade.h>
#include "ObjectPool.h"
#include "Bullet.h"

#ifndef ARRAY_LENGTH
#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))
#endif // ! ARRAY_LENGTH

class Player
{

public:

	void Tick();
	void Draw() const;

	void Move(float movementX, float movementY);
	void Shoot(float directionX, float directionY);

	const float & GetSize() const { return size; };
	const Color & GetColour() const { return colour; }
	const Vector2 & GetPosition() const { return position; }
	float GetX() const { return position.x; };
	float GetY() const { return position.y; };

	const ObjectPool<Bullet>& GetBullets() const { return bullets; }

	void IncrementUpgradeLevel(const Upgrade::UpgradeType& type);
	int GetUpgradeLevel(const Upgrade::UpgradeType& type);
	
	void Reset();

private:

	const float size = 25.0f;
	const Color colour { 0, 0, 0, 255 };

	// powerup abilities
	const int spread = 1;
	const int ticksPerShot = 10;
	int ticksSinceLastShot = 0;

	const float speed = 5.0f;

	Vector2 position{ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };

	Upgrade upgrades[4] = { Upgrade(Upgrade::UpgradeType::MoveSpeed), Upgrade(Upgrade::UpgradeType::ScoreMultiplier), Upgrade(Upgrade::UpgradeType::Damage), Upgrade(Upgrade::UpgradeType::FireRate)};

	// bullet count is framerate * shots/sec + 5 for safety
	ObjectPool<Bullet> bullets = ObjectPool<Bullet>(185);
	
};