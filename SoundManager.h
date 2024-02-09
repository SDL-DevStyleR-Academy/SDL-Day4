//SoundManager.h
#pragma once
#include "Game.h"
#include <string>
#include <map>

class SoundManager {
public:
	static SoundManager* Instance() {
		if (s_mInstance == 0) {
			s_mInstance = new SoundManager();
			return s_mInstance;
		}
		return s_mInstance;
	}

	bool load(const char* fileName, std::string id, int type);
	void playSound(std::string id, int loop, int ms = 0);
	void playMusic(std::string id, int loop, int ms = 0);
	void changeVolume(int change);
	void pauseOrPlay();
	void changeVolumeSfx(std::string id, int c);
	void setMusicPosition(double pos);

private:
	static SoundManager* s_mInstance;
	std::map<std::string, Mix_Chunk*> s_mSfxs; // keeps a list of the sound files
	std::map<std::string, Mix_Music*> s_mMusic; // keeps a list of the music files
	SoundManager();
	~SoundManager() { delete s_mInstance; };
};