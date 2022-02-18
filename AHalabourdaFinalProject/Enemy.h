#pragma once
#include "raylib.h"
#include "Poolable.h"
#include <chrono>

class Enemy : public Poolable
{

public:
	
	void Tick(const Vector2 & targetPosition);

	void Draw() const;
	bool GetIsActive() const { return mIsActive; }
	Vector2 GetPosition() const { return mPosition; }
	Rectangle GetRectangle() const { return mRect; }
	int GetAgeInMilliseconds() const;
	Color GetActualColour() const { 
		return Color{	static_cast<unsigned char>(msColour.r * (healthCurrent / healthMax)), 
						static_cast<unsigned char>(msColour.g * (healthCurrent / healthMax)),
						static_cast<unsigned char>(msColour.b * (healthCurrent / healthMax)),
						msColour.a }; }

	// takes damage
	// deactivates self if health drops below zero
	// also returns "true" if we died
	bool TakeDamage(float pDamage);

	void Activate();
	void Deactivate();

private:

	void PlaceRandomly();

	std::chrono::steady_clock::time_point mTimerBegin;
	
	// "inline" here is a c++17 thing that allows us to initialize static const member variables in-class rather than in the .cpp. very nice
	inline static const float msSize = 20.0f;
	inline static const float msGrowthRate = 1.1f;
	inline static const Color msColour{ 180, 180, 180, 200 };
	inline static const float msSpeed = 2.0f;

	Vector2 mPosition { 0, 0 };
	Rectangle mRect{ 0, 0, msSize, msSize };

	float healthMax = 100.0f;
	float healthCurrent = healthMax;

	bool mIsActive = false;

};