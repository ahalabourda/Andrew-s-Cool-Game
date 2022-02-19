#pragma once
#include <raylib.h>
#include <map>
#include <string>
class SoundManager
{

public:
	static void InitializeSounds();
	static void TriggerSound(const std::string& pSoundName);

private:
	static std::map<std::string, Sound> mSounds;

};