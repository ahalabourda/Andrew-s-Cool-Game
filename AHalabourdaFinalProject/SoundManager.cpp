#include "SoundManager.h"
#include <iostream>


std::map<std::string, Sound> SoundManager::mSounds;

void SoundManager::InitializeSounds()
{
	if (mSounds.empty()) {
		
		SoundManager::mSounds.emplace("gunshot", LoadSound("sounds/gunshot.mp3"));
		SoundManager::mSounds.emplace("impact", LoadSound("sounds/impact.mp3"));

	}
	else {
		std::cerr << "Already initialized sounds!" << std::endl;
	}

	
}

void SoundManager::TriggerSound(const std::string & pSoundName)
{
	
	// wow this is annoying
	PlaySound(mSounds.find(pSoundName)->second);

}