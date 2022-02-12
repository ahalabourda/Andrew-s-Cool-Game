#include "ChargeZone.h"

ChargeZone::ChargeZone(ChargeableAbility ca)
{

	float x = 0.0f;
	float y = 0.0f;

	switch (ca) {
	case ChargeableAbility::BulletCount:
		x = 0.0f;
		y = 0.0f;
		//colour = Color{ 242, 252, 84, 200 };
		// is this good?? the above line is presumably firing an unnecessary constructor but the bottom lines are ugly. wish there was a one liner
		mInactiveColour.r = 242;
		mInactiveColour.g = 252;
		mInactiveColour.b = 84;
		mActiveColour.r = 242;
		mActiveColour.g = 252;
		mActiveColour.b = 84;
		break;
	case ChargeableAbility::FireRate:
		x = 0.0f;
		y = (float)GetScreenHeight() / 2.0f;
		mInactiveColour.r = 91;
		mInactiveColour.g = 255;
		mInactiveColour.b = 140;
		mActiveColour.r = 91;
		mActiveColour.g = 255;
		mActiveColour.b = 140;
		break;
	case ChargeableAbility::Speed:
		x = (float)GetScreenWidth() / 2.0f;
		y = 0.0f;
		mInactiveColour.r = 133;
		mInactiveColour.g = 146;
		mInactiveColour.b = 255;
		mActiveColour.r = 133;
		mActiveColour.g = 146;
		mActiveColour.b = 255;
		break;
	case ChargeableAbility::Damage:
		x = (float)GetScreenWidth() / 2.0f;
		y = (float)GetScreenHeight() / 2.0f;
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

	mTrigger = Rectangle{ x, y, (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };
	mFiller = Rectangle{ x, y, (float)GetScreenWidth() / 2.0f, 0.0f };

}

void ChargeZone::Tick()
{

	if (mIsActive) {
		mChargeValueCurrent += mChargeAmountPerTick;
	}

}

void ChargeZone::Draw() const
{

	if (mIsActive) {
		DrawRectangle((int)mTrigger.x, (int)mTrigger.y, (int)mTrigger.width, (int)mTrigger.height, mActiveColour);
	}
	else {
		DrawRectangle((int)mTrigger.x, (int)mTrigger.y, (int)mTrigger.width, (int)mTrigger.height, mInactiveColour);
	}

	
}
