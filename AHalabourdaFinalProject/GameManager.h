#pragma once
#include "Enemy.h"
#include "ChargeZone.h"
#include "Player.h"
#include "ObjectPool.h"
#include "Bullet.h"

#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))

class GameManager
{

public:

	GameManager() = default;

	enum class GameState { Setup, Playing, PostGame };

	Player GetPlayer() const { return player; }

	void Tick();
	void Draw() const;

	GameState GetCurrentGameState() const { return currentGameState; }

	void StartGame();
	void EndGame();
	void Reset();

	Color GetBackgroundColour() const { return backgroundColour; }
	int GetScore() const { return score; }

private:

	

	// useful timer
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	GameState currentGameState = GameState::Setup;

	// hud stuff
	int score = 0;
	Color backgroundColour{ 150, 150, 150, 255 };
	Color hudColour{ 0, 0, 0, 200 };
	int fontSize = 64;

	// upgrades


	// player stuff
	Player player;

	// bullet count is framerate * shots/sec + 5 for safety
	ObjectPool<Bullet> bullets = ObjectPool<Bullet>(185);

	// charge zone stuff!
	ChargeZone zones[4] = { ChargeZone(ChargeZone::ChargeableAbility::BulletCount), ChargeZone(ChargeZone::ChargeableAbility::FireRate), ChargeZone(ChargeZone::ChargeableAbility::Speed), ChargeZone(ChargeZone::ChargeableAbility::Damage) };

	// enemy management
	ObjectPool<Enemy> enemies = ObjectPool<Enemy>(128);

	float enemySpawnFrequency = 1.0f;
	float enemySpawnAccelerationRate = 1.1f;

};