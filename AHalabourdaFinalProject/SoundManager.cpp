#include "SoundManager.h"

std::map<SoundManager::SoundKey, Sound> SoundManager::mSounds;
Music SoundManager::mMusic;

void SoundManager::InitializeSounds()
{
	if (mSounds.empty()) {
		
		SoundManager::mSounds.emplace(SoundManager::SoundKey::Gunshot, LoadSound("sounds/gunshot.mp3"));
		SoundManager::mSounds.emplace(SoundManager::SoundKey::Impact, LoadSound("sounds/impact.mp3"));
		SoundManager::mSounds.emplace(SoundManager::SoundKey::AsteroidDeath, LoadSound("sounds/asteroid-death.mp3"));
		SoundManager::mSounds.emplace(SoundManager::SoundKey::PlayerDeath, LoadSound("sounds/player-death.mp3"));
		SoundManager::mSounds.emplace(SoundManager::SoundKey::UpgradeDing, LoadSound("sounds/upgrade-ding.mp3"));

		SoundManager::mMusic = LoadMusicStream("sounds/music.mp3");

	}
	else {
		throw std::exception("Already initialized sounds!");
	}
	
}

void SoundManager::TriggerSound(SoundManager::SoundKey pSoundKey)
{
	PlaySoundMulti(mSounds.find(pSoundKey)->second);
}

void SoundManager::StartMusic()
{
	PlayMusicStream(SoundManager::mMusic);
}

void SoundManager::StopMusic()
{
	StopMusicStream(SoundManager::mMusic);
}
