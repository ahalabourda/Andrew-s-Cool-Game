#pragma once
#include "raylib.h"

class ChargeZone
{

public:

	enum class ChargeableAbility { BulletCount, FireRate, Speed, Damage };

	ChargeZone() = delete;
	ChargeZone(ChargeableAbility ca);

	Rectangle GetTriggerRect() const { return mTrigger; }
	Rectangle GetFillRect() const { return mFiller; }

	bool GetIsActive() const { return mIsActive; }
	void SetIsActive(bool newValue) { mIsActive = newValue; }

	void Tick();
	void Draw() const;

private:
	
	Rectangle mTrigger;
	Rectangle mFiller;
	Color mInactiveColour{ 0, 0, 0, 255 };
	Color mActiveColour{ 0, 0, 0, 255 };

	inline static const float msChargeValueMax = 100.0f;
	float mChargeValueCurrent = 0.0f;
	float mChargeAmountPerTick = .5f;

	bool mIsActive = false;

};