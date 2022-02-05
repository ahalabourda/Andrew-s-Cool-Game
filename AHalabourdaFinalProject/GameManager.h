#pragma once
#include "EnemyManager.h"
#include "ChargeZone.h"
#include "Player.h"
#include "ObjectPool.h"
#include "Bullet.h"

#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))

class GameManager
{

public:
	GameManager();

	Player GetPlayer() const { return player; }

	void Tick();
	void Draw() const;

private:
	//EnemyManager enemyManager;

	Player player{ 250, 350 };

	// bullet count is framerate * shots/sec + 5 for safety
	ObjectPool<Bullet> bullets = ObjectPool<Bullet>(185);

	ChargeZone zones[4] = { ChargeZone(ChargeZone::ChargeableAbility::BulletCount), ChargeZone(ChargeZone::ChargeableAbility::FireRate), ChargeZone(ChargeZone::ChargeableAbility::Speed), ChargeZone(ChargeZone::ChargeableAbility::Damage) };

};