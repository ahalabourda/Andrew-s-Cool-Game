#pragma once
class Upgrade
{

public:

	enum class UpgradeType { MoveSpeed, ScoreMultiplier, Damage, Bomb};

	Upgrade() = delete;
	Upgrade(UpgradeType type);

	int GetCurrentLevel() const { return currentLevel; }

private:

	UpgradeType thisUpgradeType;

	int currentLevel = 0;

};