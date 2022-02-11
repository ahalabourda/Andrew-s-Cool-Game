#pragma once
#include "raylib.h"

class ChargeZone
{

public:

	enum class ChargeableAbility { BulletCount, FireRate, Speed, Damage };

	ChargeZone() = delete;
	ChargeZone(ChargeableAbility ca);

	Rectangle GetTriggerRect() const { return trigger; }
	Rectangle GetFillRect() const { return fill; }

	bool GetIsActive() const { return isActive; }
	void SetIsActive(bool newValue) { isActive = newValue; }

	void Tick();
	void Draw() const;

private:
	
	Rectangle trigger;
	Rectangle fill;
	Color colour{ 0, 0, 0, 255 };
	Color activeColour{ 0, 0, 0, 255 };

	static const float chargeValueMax;
	float chargeValueCurrent = 0.0f;
	float chargeAmountPerTick = .5f;

	bool isActive = false;

};