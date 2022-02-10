#pragma once
#include "raylib.h"
#include "Poolable.h"
#include <chrono>

class Enemy : public Poolable
{

public:

	Enemy();
	
	void Tick(const Vector2 & targetPosition);

	void Draw() const;
	bool GetIsActive() const { return isActive; }
	Vector2 GetPosition() const { return position; }
	Rectangle GetRectangle() const { return rect; }
	int GetAgeInMilliseconds() const;

	void Activate();
	void Deactivate();

private:

	void PlaceRandomly();

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	static const float size;
	static const float growthRate;
	static const Color colour;
	static const float speed;
	Vector2 position { 0, 0 };
	Rectangle rect{ 0, 0, size, size };
	bool isActive = false;

};