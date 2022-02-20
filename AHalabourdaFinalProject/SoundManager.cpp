#include "SoundManager.h"
#include <iostream>


std::map<SoundManager::SoundKey, Sound> SoundManager::mSounds;

void SoundManager::InitializeSounds()
{
	if (mSounds.empty()) {
		
		SoundManager::mSounds.emplace(SoundManager::SoundKey::Gunshot, LoadSound("sounds/gunshot.mp3"));
		SoundManager::mSounds.emplace(SoundManager::SoundKey::Impact, LoadSound("sounds/impact.mp3"));
		SoundManager::mSounds.emplace(SoundManager::SoundKey::AsteroidDeath, LoadSound("sounds/asteroid-death.mp3"));
		SoundManager::mSounds.emplace(SoundManager::SoundKey::UpgradeDing, LoadSound("sounds/upgrade-ding.mp3"));

	}
	else {
		std::cerr << "Already initialized sounds!" << std::endl;
	}
	
}

void SoundManager::TriggerSound(SoundManager::SoundKey pSoundKey)
{
	
	// wow this is annoying
	PlaySoundMulti(mSounds.find(pSoundKey)->second);

}