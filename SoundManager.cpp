//SoundManager.cpp
#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager() {
	if (Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 4096) == -1) {
		std::cout << Mix_GetError() << std::endl;
	}
}

bool SoundManager::load(const char* fileName, std::string id, int type) {
	//type1 => music, type0 => sfx
	if (type == 1) { //Music
		Mix_Music* music = Mix_LoadMUS(fileName);
		if (music == 0) {
			std::cout << "Could not load music" << Mix_GetError() << std::endl;
			return false;
		}
		s_mMusic[id] = music; // save the music file in the list
		return true;
	}
	else {
		if (type == 0) { // SFX
			Mix_Chunk* chunk = Mix_LoadWAV(fileName);
			if (chunk == 0) {
				std::cout << "Could not load sfx" << Mix_GetError() << std::endl;
				return false;
			}
			s_mSfxs[id] = chunk; // save the sound file in the list
			return true;
		}
	}
	return false;
}

void SoundManager::playMusic(std::string id, int loop, int ms) { // id - which file to play
	if (Mix_FadeInMusic(s_mMusic[id], loop, ms) == -1) { // loop - how many times to start over when the file ends
		std::cout << Mix_GetError() << std::endl; // ms - fade in effect at the start of the file in milliseconds
	}
}

void SoundManager::playSound(std::string id, int loop, int ms) {
	if (Mix_FadeInChannel(-1, s_mSfxs[id], loop, ms) == -1) { // first parameter -1: play sound on an empty channel
		std::cout << Mix_GetError() << std::endl;
	}
}

void SoundManager::changeVolume(int c) { // changes the music volume by c (min-0, max-128); starts at max-128
	int currentVolume = Mix_VolumeMusic(-1); // get current volume value and decrement or increment
	currentVolume += c;
	Mix_VolumeMusic(currentVolume);
}

void SoundManager::changeVolumeSfx(std::string id, int c) { // the same as the above function but for sound volume
	int currentVolume = Mix_VolumeChunk(s_mSfxs[id], -1); // which sound file to alter needs to be specified by id
	currentVolume += c;
	Mix_VolumeChunk(s_mSfxs[id], currentVolume);
}

void SoundManager::setMusicPosition(double pos) { // pos is in seconds
	if (Mix_SetMusicPosition(pos) == -1) { // start the music file from time - pos
		std::cout << "Something failed:" << Mix_GetError() << std::endl;
	}
}

void SoundManager::pauseOrPlay() { // pauses and resumes the music

	if ( Mix_PausedMusic() == 0 ) {
		Mix_PauseMusic();
	}
	else {
		Mix_ResumeMusic();
	}


}

SoundManager* SoundManager::s_mInstance = 0;