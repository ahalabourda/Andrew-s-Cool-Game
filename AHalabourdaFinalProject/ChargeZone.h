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
	void IncrementLevel() { ++mCurrentLevel; if (mCurrentLevel > mLevelMax) { mCurrentLevel = mLevelMax; } }

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
	Color mInactiveColour{ 0, 0, 0, 255 };
	Color mActiveColour{ 0, 0, 0, 255 };
	Color mBarColour{ 30, 250, 50, 255 };

	inline static const int mLabelFontSize = 18;

	inline static const float msChargeValueMax = 100.0f;
	float mChargeValueCurrent = 0.0f;
	float mChargeAmountPerTick = .25f;

	int mCurrentLevel = 1;
	const int mLevelMax = 5;

	bool mIsActive = false;

	float GetWidth() const { return static_cast<float>(GetScreenWidth() / 2.0f); }
	float GetHeight() const { return static_cast<float>(GetScreenHeight() / 2.0f); }

};