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
	bool GetIsActive() const { return mIsActive; }
	Vector2 GetPosition() const { return mPosition; }
	Rectangle GetRectangle() const { return mRect; }
	int GetAgeInMilliseconds() const;

	void Activate();
	void Deactivate();

private:

	void PlaceRandomly();

	std::chrono::steady_clock::time_point mTimerBegin;
	
	inline static const float msSize = 20.0f;
	inline static const float msGrowthRate = 1.1f;
	inline static const Color msColour{ 200, 30, 30, 255 };
	inline static const float msSpeed = 2.0f;

	Vector2 mPosition { 0, 0 };
	Rectangle mRect{ 0, 0, msSize, msSize };
	bool mIsActive = false;

};