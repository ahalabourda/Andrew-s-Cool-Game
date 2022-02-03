#include "EnemyManager.h"

EnemyManager::EnemyManager(Player thePlayer)
	: player(thePlayer)
{
}

void EnemyManager::Tick()
{

	for (int i = 0; i < enemies.GetSize(); i++) {
		enemies.Tick();
	}

}