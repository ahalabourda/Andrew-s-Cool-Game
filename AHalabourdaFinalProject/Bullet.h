#pragma once
#include "raylib.h"
#include <chrono>
class Bullet
{

public:

	Bullet();

	void SetIsActive(bool newActiveState) { isActive = newActiveState; }
	void Activate(Vector2 spawnPosition, float spawnRotation);
	void Draw() const;
	void Tick();

	bool GetIsActive() const { return isActive; }
	const float GetDamage() const { return damage; }
	const float GetSpeed() const { return speed; }

private:
	bool isActive = false;
	
	Vector2 position{ 0, 0 };
	float rotation = 0.0f;

	std::chrono::steady_clock::time_point begin;

	// TODO: struggling to make this static.. revisit later
	const int lifespanInMilliseconds = 3000;
	const float speed = 10.0f;
	const float damage = 5.0f;
	const float size = 3.0f;

	Color colour{ 50, 50, 50, 255 };

};