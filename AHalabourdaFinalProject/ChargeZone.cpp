#include <sstream>
#include <algorithm>
#include "ChargeZone.h"


ChargeZone::ChargeZone(Upgrade::UpgradeType pUpgradeType)
	: mUpgradeType(pUpgradeType)
{

	unsigned char inactiveAlpha = 20;
	unsigned char activeAlpha = 60;
	
	switch (pUpgradeType) {
		case Upgrade::UpgradeType::MoveSpeed:

			// position
			mBasePosition = Vector2{ 0.0f, 0.0f };

			// colour
			mInactiveColour = { 242, 252, 84, inactiveAlpha };
			mActiveColour = { 242, 252, 84, activeAlpha };
			break;
		case Upgrade::UpgradeType::ScoreMultiplier:

			// position
			mBasePosition = Vector2{ 0.0f, static_cast<float>(GetScreenHeight() / 2.0f) };

			// colour
			mInactiveColour = { 91, 255, 140, inactiveAlpha };
			mActiveColour = { 91, 255, 140, activeAlpha };
			break;
		case Upgrade::UpgradeType::Damage:

			// position
			mBasePosition = Vector2{ static_cast<float>(GetScreenWidth() / 2.0f), 0.0f };

			// colour
			mInactiveColour = { 133, 146, 255, inactiveAlpha };
			mActiveColour = { 133, 146, 255, activeAlpha };
			break;
		case Upgrade::UpgradeType::FireRate:

			// position
			mBasePosition = Vector2{ static_cast<float>(GetScreenWidth() / 2.0f), static_cast<float>(GetScreenHeight() / 2.0f) };

			// colour
			mInactiveColour = { 255, 133, 133, inactiveAlpha };
			mActiveColour = { 255, 133, 133, activeAlpha };
			break;
	}

	mTrigger = Rectangle{ mBasePosition.x, mBasePosition.y, GetWidth(), GetHeight() };

}

void ChargeZone::IncrementLevel()
{
	++mCurrentLevel; 
	if (mCurrentLevel >= mLevelMax) {
		//mCurrentLevel = mLevelMax;
		mChargeBar.SetFillAmount(mChargeBar.GetFillMax() + 1);
	}
}

// "ticks" the zone, either gaining charge if the player is inside
// returns true if we leveled up this tick, returns false if not
bool ChargeZone::Tick()
{

	// already max level! bail outta here!
	if (IsMaxed()) {
		return false;
	}
	else if (mIsActive == true) {
		// the player is here! let's charge!
		
		mChargeValueCurrent = std::clamp(mChargeValueCurrent + GetActualChargeAmountPerTick(), 0.0f, mChargeBar.GetFillMax());

		mChargeBar.SetFillAmount(mChargeValueCurrent);

		// reached max charge value! level up and reset charge value!
		if (mChargeValueCurrent >= msChargeValueMax) {
			mChargeValueCurrent = 0.0f;
			IncrementLevel();
			return true;
		}
	
	}

	return false;

}

void ChargeZone::Draw() const
{

	if (mIsActive) {
		DrawRectangle((int)mTrigger.x, (int)mTrigger.y, (int)mTrigger.width, (int)mTrigger.height, mActiveColour);
	}
	else {
		DrawRectangle((int)mTrigger.x, (int)mTrigger.y, (int)mTrigger.width, (int)mTrigger.height, mInactiveColour);
	}

	// some fancy footwork to center the label
	int labelOffset = MeasureText(Upgrade::GetName(mUpgradeType).c_str(), mLabelFontSize);

	DrawText(	Upgrade::GetName(mUpgradeType).c_str(), 
				static_cast<int>(mBasePosition.x + (mTrigger.width / 2) - (labelOffset / 2)),
				static_cast<int>(mBasePosition.y + mLabelFontSize / 2),
				mLabelFontSize,
				mLabelColour);
	
	mChargeBar.Draw(Vector2{ mBasePosition.x + (mTrigger.width / 2), mBasePosition.y + (mTrigger.height / 10) }, mActiveColour);
	
	// this drawtext function really wants a C string so we do what we must.
	// i spent some time googling for simpler solutions but this was the best i could come up with before getting tired and moving on. hrm
	std::stringstream ss;
	ss << mCurrentLevel << "/" << mLevelMax;

	const std::string tmp = ss.str();

	int levelOffset = MeasureText(tmp.c_str(), mLabelFontSize);

	// some fancy footwork to center the label
	DrawText(	tmp.c_str(), 
				static_cast<int>(mBasePosition.x + (mTrigger.width / 2) - (levelOffset / 2)),
				static_cast<int>(mBasePosition.y + ChargeBar::GetHeight() * 2 + mLabelFontSize),
				mLabelFontSize,
				mLabelColour);
	
}

void ChargeZone::Reset()
{	
	mChargeValueCurrent = 0.0f;
	mChargeBar.SetFillAmount(0.0f);
	mCurrentLevel = 1;
}

float ChargeZone::GetActualChargeAmountPerTick() const
{
	return mChargeAmountPerTick * (std::powf(msChargeSlowdownModifier, mCurrentLevel - 1.0f));
}
