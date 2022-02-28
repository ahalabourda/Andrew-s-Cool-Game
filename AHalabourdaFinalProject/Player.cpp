#include "Player.h"
#include "SoundManager.h"
#include <algorithm>

#ifndef  ARRAY_LENGTH
#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))
#endif // ! ARRAY_LENGTH

Player::Player()
{


	Spawn();

	// prefill smoothing queues
	int facingsToStore = 15;
	int positionsToStore = 30;

	// these allow us to smooth out the turning animations of the tank and the cannon
	// i went back and forth a few times on whether or not the cannon should instantly turn or be smoothed
	// at present it's instant, which makes the gun facings useless.. but i think it could go either way so i'm leaving this in
	for (int i = 0; i < facingsToStore; i++) {
		mRecentBodyFacings.emplace_back(0.0f);
		mRecentGunFacings.emplace_back(0.0f);
	}

	// tank position is NOT smoothed but we use these values to smooth the shifting of the background stars! so cool
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

void Player::Move(float pMovementX, float pMovementY)
{

	// move the player, modified by movespeed powerup level, clamped between 0 and screensize so we don't escape the play area
	mPosition.x = std::clamp(mPosition.x + (pMovementX * (mSpeed + static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed) * mSpeedUpgradeValue))), 0.0f, static_cast<float>(GetScreenWidth()));
	mPosition.y = std::clamp(mPosition.y + (pMovementY * (mSpeed + static_cast<float>(GetUpgradeLevel(Upgrade::UpgradeType::MoveSpeed) * mSpeedUpgradeValue))), 0.0f, static_cast<float>(GetScreenHeight()));

	// only log a facing if we actually moved this tick
	if (pMovementX != 0.0f || pMovementY != 0.0f) {
		mRecentBodyFacings.pop_back();
		mRecentBodyFacings.push_front(((atan2f(pMovementX, -pMovementY) * 180 / PI)));
	}

	mRecentPositions.pop_back();
	mRecentPositions.push_front(mPosition);

}

// *attempts* to shoot, and only succeeds if our gun has cooled down (enough ticks have passed)
void Player::Shoot(float pDirectionX, float pDirectionY)
{

	// abstracting out the upgrade-modified fire rate
	if (mTicksSinceLastShot > GetActualTicksPerShot()) {
		mTicksSinceLastShot = 0;
		mBullets.GetNextAvailable()->Activate(mPosition, atan2f(pDirectionY, pDirectionX), GetUpgradeLevel(Upgrade::UpgradeType::Damage));
		SoundManager::TriggerSound(SoundManager::SoundKey::Gunshot);
	}

	// log a gun facing if we moved the joystick this tick
	if (pDirectionX != 0.0f || pDirectionY != 0.0f) {
		mRecentGunFacings.pop_back();
		mRecentGunFacings.push_front(atan2f(pDirectionX, -pDirectionY) * 180 / PI);
	}

}

void Player::Draw() const
{

	// we offset the tank's body because the gun isn't centered in the middle of the sprite
	Vector2 offsetPosition = mPosition;

	offsetPosition.y -= cosf(GetSmoothedAngle(mRecentBodyFacings) / 180 * PI) * mTankBody.width / 24.0f;
	offsetPosition.x += sinf(GetSmoothedAngle(mRecentBodyFacings) / 180 * PI) * mTankBody.width / 24.0f;

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
					//GetSmoothedAngle(mRecentGunFacings),
					GetLastGunFacing(),
					WHITE);

}

void Player::IncrementUpgradeLevel(Upgrade::UpgradeType pType)
{
	switch (pType) {
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

	// ding! grats
	SoundManager::TriggerSound(SoundManager::SoundKey::UpgradeDing);

}

int Player::GetUpgradeLevel(Upgrade::UpgradeType pType) const
{
	switch (pType) {
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

// some necessary gymnastics here because we want the average of 359 degrees and 1 degree to be 0, but when computed naively it averages to 180 (which is technically correct, but is not useful for our purposes)
// math stolen from: https://www.themathdoctors.org/averaging-angles/
float Player::GetSmoothedAngle(const std::deque<float>& pAngles) const
{
	float totalCosValues = 0.0f;
	float totalSinValues = 0.0f;

	for (int i = 0; i < pAngles.size(); i++) {
		totalCosValues += cosf(pAngles[i] * (PI / 180));
		totalSinValues += sinf(pAngles[i] * (PI / 180));
	}

	return atan2f(totalSinValues, totalCosValues) * (180 / PI);
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

	Spawn();

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

void Player::SetFixedStartPosition(float pX, float pY)
{
	
	float xMod = 0;
	float yMod = 0;

	if (pX >= 0.0f) {
		xMod = GetScreenWidth() / -10.0f;
	}
	else {
		xMod = GetScreenWidth() / 10.0f;
	}

	if (pY >= 0.0f) {
		yMod = GetScreenHeight() / -10.0f;
	}
	else {
		yMod = GetScreenHeight() / 10.0f;
	}

	mPosition = Vector2{ (GetScreenWidth() / 2.0f) - xMod, (GetScreenHeight() / 2.0f) - yMod };
}

void Player::Spawn()
{

	// secret feature to force spawn quadrant
	float x = GetGamepadAxisMovement(0, 0);
	float y = GetGamepadAxisMovement(0, 1);

	if (x != 0.0f && y != 0.0f) {
		SetFixedStartPosition(x, y);
	}
	else {
		// random start position
		SetRandomStartPosition();
	}

}