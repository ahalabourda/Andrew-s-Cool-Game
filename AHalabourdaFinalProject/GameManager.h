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

	const GameState& GetCurrentGameState() const { return currentGameState; }
	const Color & GetBackgroundColour() const { return backgroundColour; }
	int GetScore() const { return score; }
	int GetGameDurationInSeconds() const { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count(); }

private:

	void AttemptEnemySpawn();
	void ProcessEnemies();

	// useful timer
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	GameState currentGameState = GameState::Setup;

	// hud stuff
	int score = 0;
	const Color backgroundColour{ 150, 150, 150, 255 };
	const Color hudColour{ 0, 0, 0, 200 };
	const int fontSize = 64;

	// upgrades


	// player stuff
	Player player;

	// enemy stuff
	const int enemySpawnFrequency = 1;
	const float enemySpawnAccelerationRate = 1.1f;

	// enemy management
	ObjectPool<Enemy> enemies = ObjectPool<Enemy>(100);

	// charge zone stuff!
	ChargeZone zones[4] = { ChargeZone(ChargeZone::ChargeableAbility::BulletCount), ChargeZone(ChargeZone::ChargeableAbility::FireRate), ChargeZone(ChargeZone::ChargeableAbility::Speed), ChargeZone(ChargeZone::ChargeableAbility::Damage) };

};