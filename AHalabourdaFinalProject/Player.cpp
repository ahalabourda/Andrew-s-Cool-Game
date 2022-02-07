#include "Player.h"
#include <algorithm>

void Player::Move(float movementX, float movementY)
{

	position.x = std::clamp(position.x + (movementX * speed * static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed))), 0.0f, (float)GetScreenWidth());
	position.y = std::clamp(position.y + (movementY * speed * static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed))), 0.0f, (float)GetScreenHeight());

}

void Player::Draw() const
{

	DrawCircleV(position, size, colour);

}

int Player::GetUpgradeLevel(Upgrade::UpgradeType type)
{
	switch (type) {
	case Upgrade::UpgradeType::MoveSpeed:
		return upgrades[0].GetCurrentLevel();
	case Upgrade::UpgradeType::ScoreMultiplier:
		return upgrades[1].GetCurrentLevel();
	case Upgrade::UpgradeType::Damage:
		return upgrades[2].GetCurrentLevel();
	case Upgrade::UpgradeType::Bomb:
		return upgrades[3].GetCurrentLevel();
	}
}
