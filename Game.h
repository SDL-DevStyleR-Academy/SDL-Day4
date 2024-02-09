//Game.h
#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundManager.h"
class Game {
public:
	Game();
	~Game();
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();
	void loadAndPlaySound();
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;
};