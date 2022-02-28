#pragma once
#include <raylib.h>
#include <deque>
#include "Upgrade.h"
#include "ObjectPool.h"
#include "Bullet.h"

class Player
{

public:

	Player();

	void Tick();
	void Draw() const;

	void Move(float pMovementX, float pMovementY);
	void Shoot(float pDirectionX, float pDirectionY);

	float GetActualDamage() const { return mDamage * static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::Damage)); }
	const Vector2 & GetPosition() const { return mPosition; }

	const ObjectPool<Bullet>& GetBullets() const { return mBullets; }

	void IncrementUpgradeLevel(Upgrade::UpgradeType pType);
	int GetUpgradeLevel(Upgrade::UpgradeType pType) const;
	
	float GetLastBodyFacing() const { return mRecentBodyFacings.front(); }

	float GetLastGunFacing() const { return mRecentGunFacings.front(); }

	float GetSmoothedAngle(const std::deque<float> & pAngles) const;
	Vector2 GetSmoothedPosition(const std::deque<Vector2>& pPositions) const;
	std::deque<Vector2> GetRecentPositions() const { return mRecentPositions; }

	void Reset();

private:

	const float mDamage = 10.0f;
	const float mSpeed = 3.5f;
	const float mSpeedUpgradeValue = 1.0f;

	// powerup abilities
	const int mTicksPerShot = 12;
	int mTicksSinceLastShot = 0;

	const float mTextureScale = 0.25f;

	std::deque<Vector2> mRecentPositions;
	std::deque<float> mRecentBodyFacings;
	std::deque<float> mRecentGunFacings;

	Vector2 mPosition;

	Upgrade mUpgrades[4] = { Upgrade(Upgrade::UpgradeType::MoveSpeed), Upgrade(Upgrade::UpgradeType::ScoreMultiplier), Upgrade(Upgrade::UpgradeType::Damage), Upgrade(Upgrade::UpgradeType::FireRate)};

	// max upgraded fire rate is ~8.5/sec (60 ticks / 7 ticks per shot), with 3 second lifespan, for a worst case scenario of 26 existing bullets at a time. rounding to 32 for safety and base2 niceness
	ObjectPool<Bullet> mBullets = ObjectPool<Bullet>(32);

	const Texture2D mTankBody = LoadTexture("art/tank-body.png");
	const Texture2D mTankGun = LoadTexture("art/tank-gun.png");

	const int GetActualTicksPerShot() const { return mTicksPerShot - GetUpgradeLevel(Upgrade::UpgradeType::FireRate); }

	void Spawn();
	void SetRandomStartPosition();
	void SetFixedStartPosition(float pX, float pY);
	
};