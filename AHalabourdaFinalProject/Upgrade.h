#pragma once
class Upgrade
{

public:

	enum class UpgradeType { MoveSpeed, ScoreMultiplier, Damage, FireRate};

	Upgrade() = delete;
	Upgrade(UpgradeType type);

	void Increment() { mCurrentLevel++; }
	int GetCurrentLevel() const { return mCurrentLevel; }
	
	void Reset();

private:

	UpgradeType mUpgradeType;

	int mCurrentLevel = 1;

};