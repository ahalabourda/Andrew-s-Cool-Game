#pragma once
#include <raylib.h>
#include <Upgrade.h>
class Player
{

public:

	void Move(float movementX, float movementY);
	
	const float GetSize() const { return size; };
	const Color GetColour() const { return colour; }
	Vector2 GetPosition() const { return position; }
	float GetX() const { return position.x; };
	float GetY() const { return position.y; };

	void Draw() const;

	int GetUpgradeLevel(Upgrade::UpgradeType type);

private:

	const float size = 25.0f;
	const Color colour { 0, 0, 0, 255 };

	// powerup abilities
	int spread = 1;
	int fireRate = 1;

	float speed = 5.0f;

	Vector2 position{ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };

	Upgrade upgrades[4] = { Upgrade(Upgrade::UpgradeType::MoveSpeed), Upgrade(Upgrade::UpgradeType::ScoreMultiplier), Upgrade(Upgrade::UpgradeType::Damage), Upgrade(Upgrade::UpgradeType::Bomb)};
	
};