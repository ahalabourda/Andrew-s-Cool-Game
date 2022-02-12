#pragma once
#include "Enemy.h"
#include "ObjectPool.h"
#include <chrono>
#include <Player.h>

class EnemyManager
{

public:

	EnemyManager() = delete;
	EnemyManager(Player thePlayer);

	void Tick();

private:
	ObjectPool<Enemy> mEnemies = ObjectPool<Enemy>(100);

	Player mPlayer;
	float spawnFrequency = 1.0f;
	float spawnAccelerationRate = 1.1f;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

};