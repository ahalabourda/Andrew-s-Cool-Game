#include "Player.h"
#include <algorithm>

void Player::Tick()
{

	ticksSinceLastShot++;

	// moving
	Move(GetGamepadAxisMovement(0, 0), GetGamepadAxisMovement(0, 1));

	// shooting
	if (GetGamepadAxisMovement(0, 2) || GetGamepadAxisMovement(0, 3)) {
		Shoot(GetGamepadAxisMovement(0, 2), GetGamepadAxisMovement(0, 3));
	}
}

void Player::Move(float movementX, float movementY)
{

	position.x = std::clamp(position.x + (movementX * speed * static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed))), 0.0f, (float)GetScreenWidth());
	position.y = std::clamp(position.y + (movementY * speed * static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed))), 0.0f, (float)GetScreenHeight());

}

void Player::Shoot(float directionX, float directionY)
{

	if (ticksSinceLastShot > ticksPerShot) {
		ticksSinceLastShot = 0;
		bullets.GetNextAvailable()->Activate(position, atan2f(directionY, directionX));
	}
}

void Player::Draw() const
{
	DrawCircleV(position, size, colour);
}

void Player::IncrementUpgradeLevel(const Upgrade::UpgradeType& type)
{
	switch (type) {
		case Upgrade::UpgradeType::MoveSpeed:
			upgrades[0].Increment();
			break;
		case Upgrade::UpgradeType::ScoreMultiplier:
			upgrades[1].Increment();
			break;
		case Upgrade::UpgradeType::Damage:
			upgrades[2].Increment();
			break;
		case Upgrade::UpgradeType::FireRate:
			upgrades[3].Increment();
			break;
	}
}

int Player::GetUpgradeLevel(const Upgrade::UpgradeType& type)
{
	switch (type) {
		case Upgrade::UpgradeType::MoveSpeed:
			return upgrades[0].GetCurrentLevel();
		case Upgrade::UpgradeType::ScoreMultiplier:
			return upgrades[1].GetCurrentLevel();
		case Upgrade::UpgradeType::Damage:
			return upgrades[2].GetCurrentLevel();
		case Upgrade::UpgradeType::FireRate:
			return upgrades[3].GetCurrentLevel();
		default:
			return -1;
	}
}

void Player::Reset()
{

	position = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };

	for (int i = 0; i < ARRAY_LENGTH(upgrades); i++) {
		upgrades[i].Reset();
	}

	bullets.Reset();

}
