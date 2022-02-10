#pragma once
#include "raylib.h"
#include "Poolable.h"
#include <chrono>
class Bullet : public Poolable
{

public:

	Bullet();

	void SetIsActive(bool newActiveState) { isActive = newActiveState; }
	void Activate(Vector2 spawnPosition, float spawnRotation);
	void Deactivate();
	void Draw() const;
	void Tick();

	bool GetIsActive() const { return isActive; }
	Vector2 GetPosition() const { return position; }
	float GetDamage() const { return damage; }
	float GetSpeed() const { return speed; }
	float GetSize() const { return size; }

private:

	std::chrono::steady_clock::time_point begin;

	Vector2 position{ 0, 0 };
	float rotation = 0.0f;

	// TODO: struggling to make this static.. revisit later
	const int lifespanInMilliseconds = 3000;
	const float speed = 10.0f;
	const float damage = 5.0f;
	const float size = 3.0f;

	Color colour{ 50, 50, 50, 255 };

	bool isActive = false;

};