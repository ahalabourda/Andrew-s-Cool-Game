#include "Player.h"
#include <algorithm>

void Player::Tick()
{

	mTicksSinceLastShot++;

	// moving
	Move(GetGamepadAxisMovement(0, 0), GetGamepadAxisMovement(0, 1));

	// shooting
	if (GetGamepadAxisMovement(0, 2) || GetGamepadAxisMovement(0, 3)) {
		Shoot(GetGamepadAxisMovement(0, 2), GetGamepadAxisMovement(0, 3));
	}
}

void Player::Move(float movementX, float movementY)
{

	mPosition.x = std::clamp(mPosition.x + (movementX * mSpeed * static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed))), 0.0f, (float)GetScreenWidth());
	mPosition.y = std::clamp(mPosition.y + (movementY * mSpeed * static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed))), 0.0f, (float)GetScreenHeight());

}

void Player::Shoot(float directionX, float directionY)
{

	if (mTicksSinceLastShot > mTicksPerShot) {
		mTicksSinceLastShot = 0;
		mBullets.GetNextAvailable()->Activate(mPosition, atan2f(directionY, directionX));
	}
}

void Player::Draw() const
{
	DrawCircleV(mPosition, mSize, mColour);
}

void Player::IncrementUpgradeLevel(const Upgrade::UpgradeType& type)
{
	switch (type) {
		case Upgrade::UpgradeType::MoveSpeed:
			mUpgrades[0].Increment();
			break;
		case Upgrade::UpgradeType::ScoreMultiplier:
			mUpgrades[1].Increment();
			break;
		case Upgrade::UpgradeType::Damage:
			mUpgrades[2].Increment();
			break;
		case Upgrade::UpgradeType::FireRate:
			mUpgrades[3].Increment();
			break;
	}
}

int Player::GetUpgradeLevel(const Upgrade::UpgradeType& type)
{
	switch (type) {
		case Upgrade::UpgradeType::MoveSpeed:
			return mUpgrades[0].GetCurrentLevel();
		case Upgrade::UpgradeType::ScoreMultiplier:
			return mUpgrades[1].GetCurrentLevel();
		case Upgrade::UpgradeType::Damage:
			return mUpgrades[2].GetCurrentLevel();
		case Upgrade::UpgradeType::FireRate:
			return mUpgrades[3].GetCurrentLevel();
		default:
			return -1;
	}
}

void Player::Reset()
{

	mPosition = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };

	for (int i = 0; i < ARRAY_LENGTH(mUpgrades); i++) {
		mUpgrades[i].Reset();
	}

	mBullets.Reset();

}
