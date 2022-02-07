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
			colour.r = 242;
			colour.g = 252;
			colour.b = 84;
			activeColour.r = 242;
			activeColour.g = 252;
			activeColour.b = 84;
			break;
		case ChargeableAbility::FireRate:
			x = 0.0f;
			y = (float)GetScreenHeight() / 2.0f;
			colour.r = 91;
			colour.g = 255;
			colour.b = 140;
			activeColour.r = 91;
			activeColour.g = 255;
			activeColour.b = 140;
			break;
		case ChargeableAbility::Speed:
			x = (float)GetScreenWidth() / 2.0f;
			y = 0.0f;
			colour.r = 133;
			colour.g = 146;
			colour.b = 255;
			activeColour.r = 133;
			activeColour.g = 146;
			activeColour.b = 255;
			break;
		case ChargeableAbility::Damage:
			x = (float)GetScreenWidth() / 2.0f;
			y = (float)GetScreenHeight() / 2.0f;
			colour.r = 255;
			colour.g = 133;
			colour.b = 133;
			activeColour.r = 255;
			activeColour.g = 133;
			activeColour.b = 133;
			break;
	}

	colour.a = 50;
	activeColour.a = 255;

	trigger = Rectangle{ x, y, (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };

}

void ChargeZone::Tick()
{

	if (isActive) {
		chargeValueCurrent += chargeAmountPerTick;
	}

}

void ChargeZone::Draw() const
{

	if (isActive) {
		DrawRectangle((int)trigger.x, (int)trigger.y, (int)trigger.width, (int)trigger.height, activeColour);
	}
	else {
		DrawRectangle((int)trigger.x, (int)trigger.y, (int)trigger.width, (int)trigger.height, colour);
	}

	
}
