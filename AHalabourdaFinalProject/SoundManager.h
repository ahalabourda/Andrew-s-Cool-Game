#pragma once
#include <raylib.h>
#include <map>
#include <string>
class SoundManager
{

public:

	enum class SoundKey { Gunshot, Impact, AsteroidDeath, PlayerDeath, UpgradeDing };

	static void InitializeSounds();
	static void TriggerSound(SoundManager::SoundKey pSoundKey);

private:
	static std::map<SoundManager::SoundKey, Sound> mSounds;

};