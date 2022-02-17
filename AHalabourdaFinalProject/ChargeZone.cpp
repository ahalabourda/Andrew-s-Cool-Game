#include <sstream>
#include "ChargeZone.h"


ChargeZone::ChargeZone(Upgrade::UpgradeType pUpgradeType)
	: mUpgradeType(pUpgradeType)
{
	
	switch (pUpgradeType) {
		case Upgrade::UpgradeType::MoveSpeed:

			// position
			mBasePosition = Vector2{ 0.0f, 0.0f };



			// colour
			// mActiveColour = Color{ 242, 252, 84, 200 };
			// is this good?? the above line is presumably firing an unnecessary constructor but the bottom lines are ugly. wish there was a one liner
			mInactiveColour.r = 242;
			mInactiveColour.g = 252;
			mInactiveColour.b = 84;
			mActiveColour.r = 242;
			mActiveColour.g = 252;
			mActiveColour.b = 84;
			break;
		case Upgrade::UpgradeType::ScoreMultiplier:

			// position
			mBasePosition = Vector2{ 0.0f, static_cast<float>(GetScreenHeight() / 2.0f) };

			// colour
			mInactiveColour.r = 91;
			mInactiveColour.g = 255;
			mInactiveColour.b = 140;
			mActiveColour.r = 91;
			mActiveColour.g = 255;
			mActiveColour.b = 140;
			break;
		case Upgrade::UpgradeType::Damage:

			// position
			mBasePosition = Vector2{ static_cast<float>(GetScreenWidth() / 2.0f), 0.0f };

			// colour
			mInactiveColour.r = 133;
			mInactiveColour.g = 146;
			mInactiveColour.b = 255;
			mActiveColour.r = 133;
			mActiveColour.g = 146;
			mActiveColour.b = 255;
			break;
		case Upgrade::UpgradeType::FireRate:

			// position
			mBasePosition = Vector2{ static_cast<float>(GetScreenWidth() / 2.0f), static_cast<float>(GetScreenHeight() / 2.0f) };

			mInactiveColour.r = 255;
			mInactiveColour.g = 133;
			mInactiveColour.b = 133;
			mActiveColour.r = 255;
			mActiveColour.g = 133;
			mActiveColour.b = 133;
			break;
	}

	mInactiveColour.a = 50;
	mActiveColour.a = 255;

	mTrigger = Rectangle{ mBasePosition.x, mBasePosition.y, GetWidth(), GetHeight() };

}

bool ChargeZone::Tick()
{

	if (mIsActive) {

		if (mCurrentLevel == mLevelMax) {
			// sort of a hack to detect when the bar is fully filled
			mChargeBar.SetFillAmount(mChargeBar.GetFillMax() + 1);
			return false;
		}
		else {
			mChargeValueCurrent += mChargeAmountPerTick;

			mChargeBar.SetFillAmount(mChargeValueCurrent);

			if (mChargeValueCurrent >= msChargeValueMax) {
				IncrementLevel();
				mChargeValueCurrent = 0.0f;
				return true;
			}

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

	int labelOffset = MeasureText(Upgrade::GetName(mUpgradeType).c_str(), mLabelFontSize);

	DrawText(	Upgrade::GetName(mUpgradeType).c_str(), 
				static_cast<int>(mBasePosition.x + (mTrigger.width / 2) - (labelOffset / 2)),
				static_cast<int>(mBasePosition.y + mLabelFontSize / 2),
				mLabelFontSize, 
				BLACK);
	
	mChargeBar.Draw(Vector2{ mBasePosition.x + (mTrigger.width / 2), mBasePosition.y + (mTrigger.height / 10) }, mActiveColour);
	
	// i hate this
	// TODO: make it so i don't hate it
	std::stringstream ss;
	ss << mCurrentLevel << "/" << mLevelMax;

	const std::string tmp = ss.str();

	int levelOffset = MeasureText(tmp.c_str(), mLabelFontSize);

	// okay this has to be horrible
	DrawText(	tmp.c_str(), 
				static_cast<int>(mBasePosition.x + (mTrigger.width / 2) - (levelOffset / 2)),
				static_cast<int>(mBasePosition.y + mChargeBar.GetHeight() * 4 + mLabelFontSize), 
				//static_cast<int>(mBasePosition.y + mLabelFontSize / 2),
				mLabelFontSize, 
				BLACK);
	
}

void ChargeZone::Reset()
{
	
	mChargeValueCurrent = 0.0f;
	mCurrentLevel = 1;

}