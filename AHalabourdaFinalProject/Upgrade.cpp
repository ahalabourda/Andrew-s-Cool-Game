#include "Upgrade.h"

Upgrade::Upgrade(UpgradeType pType)
	: mUpgradeType(pType)
{
}

std::string Upgrade::GetName(Upgrade::UpgradeType pUpgradeType)
{
	switch (pUpgradeType) {
	case UpgradeType::MoveSpeed:
		return "Move Speed";
	case UpgradeType::ScoreMultiplier:
		return "Score Multiplier";
	case UpgradeType::Damage:
		return "Damage";
	case UpgradeType::FireRate:
		return "Fire Rate";
	default:
		return "Unknown upgrade!";
	}
}

void Upgrade::Reset()
{
	mCurrentLevel = 1;
}