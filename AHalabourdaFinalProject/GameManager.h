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

	// these two are const references to prevent a copy
	const GameState & GetCurrentGameState() const { return mCurrentGameState; }
	const Color & GetBackgroundColour() const { return mBackgroundColour; }

	int GetScore() const { return mScore; }
	int GetGameDurationInSeconds() const { return static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - mTimerBegin).count()); }
	int GetGameDurationInMilliseconds() const { return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mTimerBegin).count()); }

private:

	void ProcessSpawning();
	void ProcessEnemies();
	void ProcessBullets();
	void ProcessZones();

	// player stuff
	Player mPlayer;

	// useful timer
	std::chrono::steady_clock::time_point mTimerBegin = std::chrono::steady_clock::now();

	GameState mCurrentGameState = GameState::Setup;

	// hud stuff
	int mScore = 0;
	const Color mBackgroundColour{ 150, 150, 150, 255 };
	const Color mHudColour{ 255, 255, 255, 200 };
	const int mFontSize = 64;

	// upgrades

	// enemy stuff
	const int mTicksPerEnemySpawnBase = 100;
	const float mEnemySpawnAccelerationRate = .8f;
	int mTicksSinceLastEnemySpawn = 0;

	int GetActualTicksPerEnemySpawn() const;

	int mCurrentDifficultyLevel = 1;
	const int mLevelDurationInSeconds = 20;

	// enemy management
	ObjectPool<Enemy> mEnemies = ObjectPool<Enemy>(128);

	// charge zone stuff!
	ChargeZone mZones[4] = { ChargeZone(Upgrade::UpgradeType::MoveSpeed), ChargeZone(Upgrade::UpgradeType::ScoreMultiplier), ChargeZone(Upgrade::UpgradeType::Damage), ChargeZone(Upgrade::UpgradeType::FireRate) };
	ChargeZone* mActiveZone = &mZones[0];

	const Texture2D mBackground = LoadTexture("art/space.png");

};