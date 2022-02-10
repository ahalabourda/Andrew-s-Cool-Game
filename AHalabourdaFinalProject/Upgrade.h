#pragma once
class Upgrade
{

public:

	enum class UpgradeType { MoveSpeed, ScoreMultiplier, Damage, FireRate};

	Upgrade() = delete;
	Upgrade(UpgradeType type);

	void Increment() { currentLevel++; }
	int GetCurrentLevel() const { return currentLevel; }
	
	void Reset();

private:

	UpgradeType thisUpgradeType;

	int currentLevel = 1;

};