#pragma once
#include "raylib.h"
#include "Upgrade.h"
#include "ChargeBar.h"

class ChargeZone
{

public:

	ChargeZone() = delete;
	ChargeZone(Upgrade::UpgradeType pUpgradeType);

	Rectangle GetTriggerRect() const { return mTrigger; }

	
	bool GetIsActive() const { return mIsActive; }
	void SetIsActive(bool newValue) { mIsActive = newValue; }
	int GetCurrentLevel() const { return mCurrentLevel; }
	//void IncrementLevel() { ++mCurrentLevel; mChargeAmountPerTick *= msChargeSlowdownModifier; if (mCurrentLevel > mLevelMax) { mCurrentLevel = mLevelMax; } }
	void IncrementLevel() { ++mCurrentLevel; if (mCurrentLevel > mLevelMax) { mCurrentLevel = mLevelMax; } }
	bool IsMaxed() const { return mCurrentLevel >= mLevelMax; }

	Upgrade::UpgradeType GetUpgradeType() const { return mUpgradeType; }

	// returns TRUE if we dinged on this tick
	bool Tick();
	void Draw() const;

	void Reset();

private:
	
	Vector2 mBasePosition;

	ChargeBar mChargeBar;

	Upgrade::UpgradeType mUpgradeType;

	Rectangle mTrigger;

	// these colours get set in the constructor based on what type of upgrade this zone corresponds to
	Color mInactiveColour; 
	Color mActiveColour;
	Color mBarColour;
	inline static const Color mLabelColour{ 255, 255, 255, 200 };

	inline static const int mLabelFontSize = 18;

	inline static const float msChargeValueMax = 100.0f;
	inline static const float msChargeSlowdownModifier = 0.8f;
	inline static const float mChargeAmountPerTick = 0.2f;
	inline static const float mDrainAmountPerTick = 0.2f;
	float mChargeValueCurrent = 0.0f;

	int mCurrentLevel = 1;
	inline static const int mLevelMax = 5;

	bool mIsActive = false;

	static float GetWidth() { return static_cast<float>(GetScreenWidth() / 2.0f); }
	static float GetHeight() { return static_cast<float>(GetScreenHeight() / 2.0f); }
	float GetActualChargeAmountPerTick() const;

};