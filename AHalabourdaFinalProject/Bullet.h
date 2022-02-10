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
	float GetDamage() const { return Bullet::damage; }
	float GetSpeed() const { return Bullet::speed; }
	float GetSize() const { return Bullet::size; }

private:

	std::chrono::steady_clock::time_point begin;

	Vector2 position{ 0, 0 };
	float rotation = 0.0f;

	// static const int can be declared in here, but not the floats? weird quirk but stackoverflow seems to corroborate: https://stackoverflow.com/questions/185844/how-to-initialize-private-static-members-in-c
	static const int lifespanInMilliseconds = 3000; 
	static const float speed;
	static const float damage;
	static const float size;

	Color colour{ 50, 50, 50, 255 };

	bool isActive = false;

};