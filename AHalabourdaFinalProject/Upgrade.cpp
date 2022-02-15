#include "Upgrade.h"

Upgrade::Upgrade(UpgradeType type)
	: mUpgradeType(type)
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
		return "Bullet Damage";
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