#pragma once
#include "Enemy.h"
#include "ChargeZone.h"
#include "Player.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include <chrono>

#ifndef  ARRAY_LENGTH
#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))
#endif // ! ARRAY_LENGTH

class GameManager
{

public:

	GameManager() = default;

	enum class GameState { Setup, Playing, PostGame };

	void Tick();
	void Draw() const;

	void StartGame();
	void EndGame();
	void Reset();

	const GameState& GetCurrentGameState() const { return mCurrentGameState; }
	const Color & GetBackgroundColour() const { return mBackgroundColour; }
	int GetScore() const { return mScore; }
	int GetGameDurationInSeconds() const { return static_cast<int>( std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - mTimerBegin).count()); }

private:

	void AttemptEnemySpawn();
	void ProcessEnemies();

	// useful timer
	std::chrono::steady_clock::time_point mTimerBegin = std::chrono::steady_clock::now();

	GameState mCurrentGameState = GameState::Setup;

	// hud stuff
	int mScore = 0;
	const Color mBackgroundColour{ 150, 150, 150, 255 };
	const Color mHudColour{ 0, 0, 0, 200 };
	const int mFontSize = 64;

	// upgrades


	// player stuff
	Player mPlayer;

	// enemy stuff
	const int mEnemySpawnFrequency = 1;
	const float mEnemySpawnAccelerationRate = 1.1f;

	// enemy management
	ObjectPool<Enemy> mEnemies = ObjectPool<Enemy>(100);

	// charge zone stuff!
	ChargeZone mZones[4] = { ChargeZone(ChargeZone::ChargeableAbility::BulletCount), ChargeZone(ChargeZone::ChargeableAbility::FireRate), ChargeZone(ChargeZone::ChargeableAbility::Speed), ChargeZone(ChargeZone::ChargeableAbility::Damage) };

};