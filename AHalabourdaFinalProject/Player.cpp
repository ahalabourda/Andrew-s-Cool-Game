#include "Player.h"
#include "raymath.h"
#include "SoundManager.h"
#include <math.h>
#include <algorithm>
#include <iostream>

Player::Player()
{

	// random start position
	SetRandomStartPosition();

	// prefill smoothing queues
	int facingsToStore = 10;
	int positionsToStore = 30;

	for (int i = 0; i < facingsToStore; i++) {
		mRecentBodyFacings.emplace_back(0.0f);
		mRecentGunFacings.emplace_back(0.0f);
	}

	for (int i = 0; i < positionsToStore; i++) {
		mRecentPositions.emplace_back(mPosition);
	}

}

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

	mPosition.x = std::clamp(mPosition.x + (movementX * (mSpeed + static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed) * mSpeedUpgradeValue))), 0.0f, (float)GetScreenWidth());
	mPosition.y = std::clamp(mPosition.y + (movementY * (mSpeed + static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed) * mSpeedUpgradeValue))), 0.0f, (float)GetScreenHeight());

	if (movementX != 0.0f || movementY != 0.0f) {
		//mLatestBodyFacing = atan2f(movementX, -movementY) * 180 / 3.141592653f;

		mRecentBodyFacings.pop_back();
		mRecentBodyFacings.push_front(((atan2f(movementX, -movementY) * 180 / 3.141592653f)));
	}

	mRecentPositions.pop_back();
	mRecentPositions.push_front(mPosition);

}

void Player::Shoot(float directionX, float directionY)
{

	if (mTicksSinceLastShot > GetActualTicksPerShot()) {
		mTicksSinceLastShot = 0;
		mBullets.GetNextAvailable()->Activate(mPosition, atan2f(directionY, directionX));
		SoundManager::TriggerSound("gunshot");
		//PlaySound(LoadSound("sounds/gunshot.mp3"));
	}

	if (directionX != 0.0f || directionY != 0.0f) {
		mRecentGunFacings.pop_back();
		mRecentGunFacings.push_front(atan2f(directionX, -directionY) * 180 / 3.141592653f);
	}
}

void Player::Draw() const
{

	// we offset the tank's body because the gun isn't centered in the middle of the sprite
	Vector2 offsetPosition = mPosition;

	offsetPosition.y -= cosf(GetSmoothedAngle(mRecentBodyFacings) / 180 * 3.141592653f) * mTankBody.width / 24.0f;
	offsetPosition.x += sinf(GetSmoothedAngle(mRecentBodyFacings) / 180 * 3.141592653f) * mTankBody.width / 24.0f;

	// these `mTextureScale * 2` expressions evaluate to 1. lol. oh well good practice anyway
	DrawTexturePro(	mTankBody,
					Rectangle{ 0.0f, 0.0f, static_cast<float>(mTankBody.width), static_cast<float>(mTankBody.height) },
					Rectangle{ offsetPosition.x, offsetPosition.y, static_cast<float>(mTankBody.width) * mTextureScale, static_cast<float>(mTankBody.height) * mTextureScale },
					Vector2{ static_cast<float>(mTankBody.width * mTextureScale / 2), static_cast<float>(mTankBody.height * mTextureScale / 2) },
					GetSmoothedAngle(mRecentBodyFacings),
					WHITE);

	DrawTexturePro(	mTankGun,
					Rectangle{ 0.0f, 0.0f, static_cast<float>(mTankGun.width), static_cast<float>(mTankGun.height) },
					Rectangle{ mPosition.x, mPosition.y, static_cast<float>(mTankGun.width) * mTextureScale, static_cast<float>(mTankGun.height) * mTextureScale },
					Vector2{ static_cast<float>(mTankGun.width * mTextureScale / 2), static_cast<float>(mTankGun.height * mTextureScale / 1.25f) },
					GetSmoothedAngle(mRecentGunFacings),
					WHITE);

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

int Player::GetUpgradeLevel(const Upgrade::UpgradeType& type) const
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

// had to steal this math from: https://www.themathdoctors.org/averaging-angles/
// good thing to learn though
float Player::GetSmoothedAngle(const std::deque<float>& pAngles) const
{
	float totalCosValues = 0.0f;
	float totalSinValues = 0.0f;

	for (int i = 0; i < pAngles.size(); i++) {
		totalCosValues += cos(pAngles[i] * (3.141592653f / 180));
		totalSinValues += sin(pAngles[i] * (3.141592653f / 180));
	}

	return atan2f(totalSinValues, totalCosValues) * (180 / 3.141592653f);
}

Vector2 Player::GetSmoothedPosition(const std::deque<Vector2>& pPositions) const
{

	float xSum = 0;
	float ySum = 0;

	for (int i = 0; i < pPositions.size(); i++) {
		xSum += pPositions[i].x;
		ySum += pPositions[i].y;
	}

	return Vector2{ xSum / pPositions.size(), ySum / pPositions.size() };
}

void Player::Reset()
{

	// random start position
	SetRandomStartPosition();

	for (int i = 0; i < ARRAY_LENGTH(mUpgrades); i++) {
		mUpgrades[i].Reset();
	}

	for (int i = 0; i < mRecentPositions.size(); i++) {
		mRecentPositions[i] = mPosition;
	}

	// slightly dangerous since we are trusting that we are tracking the same number of recent facings for the tank body and the tank gun
	for (int i = 0; i < mRecentBodyFacings.size(); i++) {
		mRecentBodyFacings[i] = 0.0f;
		mRecentGunFacings[i] = 0.0f;
	}

	mBullets.Reset();

}

void Player::SetRandomStartPosition()
{

	srand(static_cast<int>(time(NULL)));

	int spawnPicker = rand() % 4;
	float xMod = 0;
	float yMod = 0;

	switch (spawnPicker) {
	case 0:
		xMod = GetScreenWidth() / 10.0f;
		yMod = GetScreenHeight() / 10.0f;
		break;
	case 1:
		xMod = GetScreenWidth() / -10.0f;
		yMod = GetScreenHeight() / 10.0f;
		break;
	case 2:
		xMod = GetScreenWidth() / 10.0f;
		yMod = GetScreenHeight() / -10.0f;
		break;
	case 3:
		xMod = GetScreenWidth() / -10.0f;
		yMod = GetScreenHeight() / -10.0f;
		break;
	}

	mPosition = Vector2{ (GetScreenWidth() / 2.0f) - xMod, (GetScreenHeight() / 2.0f) - yMod };
}
