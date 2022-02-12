#include "Upgrade.h"

Upgrade::Upgrade(UpgradeType type)
	: mUpgradeType(type)
{
}

void Upgrade::Reset()
{

	mCurrentLevel = 1;

}