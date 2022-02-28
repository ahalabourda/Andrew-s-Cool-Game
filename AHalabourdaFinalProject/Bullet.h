#pragma once
#include "raylib.h"
#include "Poolable.h"
#include <chrono>
class Bullet : public Poolable
{

public:

	void SetIsActive(bool pActiveState) { mIsActive = pActiveState; }
	void Activate(Vector2 pSpawnPosition, float pSpawnRotation, int pDamageLevel);
	void Deactivate();
	void Draw() const;
	void Tick();

	bool GetIsActive() const { return mIsActive; }
	Vector2 GetPosition() const { return mPosition; }
	float GetSpeed() const { return Bullet::msSpeed; }
	float GetSize() const { return Bullet::msSize; }

	static void InitializeSprites();

private:

	std::chrono::steady_clock::time_point mTimerBegin;
	
	static Texture2D mSprites[5];
	Texture2D* mActiveSprite;

	Vector2 mPosition{ 0, 0 };
	float mRotation = 0.0f;

	// static const int can be declared in here, but not the floats? weird quirk but stackoverflow seems to corroborate: https://stackoverflow.com/questions/185844/how-to-initialize-private-static-members-in-c
	inline static const int msLifespanInMilliseconds = 3000; 
	inline static const float msSize = 5.0f;
	inline static const float msSpeed = 10.0f;

	bool mIsActive = false;

};