#pragma once
#include <raylib.h>
#include <deque>
#include "Upgrade.h"
#include "ObjectPool.h"
#include "Bullet.h"

#ifndef ARRAY_LENGTH
#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))
#endif // ! ARRAY_LENGTH

class Player
{

public:

	Player();

	void Tick();
	void Draw() const;

	void Move(float movementX, float movementY);
	void Shoot(float directionX, float directionY);

	const float GetActualDamage() const { return mDamage * static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::Damage)); }
	const float & GetSize() const { return mSize; };
	const Color & GetColour() const { return mColour; }
	const Vector2 & GetPosition() const { return mPosition; }
	float GetX() const { return mPosition.x; };
	float GetY() const { return mPosition.y; };

	const ObjectPool<Bullet>& GetBullets() const { return mBullets; }

	void IncrementUpgradeLevel(const Upgrade::UpgradeType& type);
	int GetUpgradeLevel(const Upgrade::UpgradeType& type) const;
	
	float GetLastBodyFacing() const { return mRecentBodyFacings.back(); }

	float GetLastGunFacing() const { return mRecentGunFacings.back(); }

	float GetSmoothedAngle(const std::deque<float> & pAngles) const;
	Vector2 GetSmoothedPosition(const std::deque<Vector2>& pPositions) const;
	std::deque<Vector2> GetRecentPositions() const { return mRecentPositions; }

	void Reset();

private:

	const float mDamage = 10.0f;
	const float mSpeed = 3.5f;
	const float mSpeedUpgradeValue = 1.5f;
	const float mSize = 25.0f;
	const Color mColour { 0, 0, 0, 255 };
	const Color mBorderColour{ 255, 255, 255, 255 };

	const Texture2D mTankBody = LoadTexture("art/tank-body.png");
	const Texture2D mTankGun = LoadTexture("art/tank-gun.png");
	const float mTextureScale = 0.25f;

	// powerup abilities
	const int mSpread = 1;
	const int mTicksPerShot = 8;
	int mTicksSinceLastShot = 0;

	std::deque<Vector2> mRecentPositions;
	std::deque<float> mRecentBodyFacings;
	std::deque<float> mRecentGunFacings;

	Vector2 mPosition;
	//Vector2 mPosition{ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };

	Upgrade mUpgrades[4] = { Upgrade(Upgrade::UpgradeType::MoveSpeed), Upgrade(Upgrade::UpgradeType::ScoreMultiplier), Upgrade(Upgrade::UpgradeType::Damage), Upgrade(Upgrade::UpgradeType::FireRate)};

	// bullet count is framerate * shots/sec + 5 for safety
	ObjectPool<Bullet> mBullets = ObjectPool<Bullet>(185);

	const int GetActualTicksPerShot() const { return mTicksPerShot - GetUpgradeLevel(Upgrade::UpgradeType::FireRate); }
	void SetRandomStartPosition();
	
};