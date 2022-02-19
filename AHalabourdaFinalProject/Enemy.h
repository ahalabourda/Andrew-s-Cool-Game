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
	Rectangle GetActualRectangle() const { return Rectangle{ mPosition.x, mPosition.y, static_cast<float>(mSprite.width) * mTextureScale, static_cast<float>(mSprite.height) * mTextureScale }; }
	int GetAgeInMilliseconds() const;
	Color GetActualColour() const { 
		return Color{	static_cast<unsigned char>(msColour.r * (mHealthCurrent / mHealthMax)), 
						static_cast<unsigned char>(msColour.g * (mHealthCurrent / mHealthMax)),
						static_cast<unsigned char>(msColour.b * (mHealthCurrent / mHealthMax)),
						msColour.a }; }
	bool IsCollidingWithPlayer(const Vector2 & pPlayerPosition);

	// takes damage
	// deactivates self if health drops below zero
	// also returns "true" if we died so game manager can know
	bool TakeDamage(float pDamage);

	void Activate();
	void Deactivate();

	static void InitializeSprite();

private:

	void PlaceRandomly();

	std::chrono::steady_clock::time_point mTimerBegin;
	
	// "inline" here is a c++17 thing that allows us to initialize static const member variables in-class rather than in the .cpp. very nice
	inline static const float msSize = 20.0f;
	inline static const float msGrowthRate = 1.1f;
	inline static const Color msColour{ 180, 180, 180, 255 };
	inline static const float msSpeed = 2.0f;
	float mTextureScale = 1.0f;

	Vector2 mPosition { 0, 0 };
	Rectangle mRect{ 0, 0, msSize, msSize };

	// unsure if i can actually make this static... :/
	// getting deep, confusing raylib access violations when i try
	// would be nice to not have 128 dupes of this texture floating around though
	static Texture2D mSprite;

	inline static float mHealthMax = 100.0f;
	float mHealthCurrent = mHealthMax;

	float mBaseRotation = static_cast<float>(rand() % 360);
	float mRotationSpeed = ((rand() % 10) - 5.0f) / 100.0f;

	bool mIsActive = false;

};