#include "Upgrade.h"

Upgrade::Upgrade(UpgradeType type)
	: thisUpgradeType(type)
{
}

void Upgrade::Reset()
{

	currentLevel = 1;

}