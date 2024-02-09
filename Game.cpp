//Game.cpp
#include "Game.h"
#include <iostream>

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != 0) //window init success
		{
			std::cout << "window creation success\n";
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != 0) //renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			}
			else {
				std::cout << "renderer init failed\n";
				return false;
			}
		}
		else {
			std::cout << "window init failed\n";
			return false;
		}
	}
	else {
		std::cout << "SDL init fail\n";
		return false;
	}
	std::cout << "init success\n";
	running = true;
	return true;
}

void Game::loadAndPlaySound() {
	SoundManager::Instance()->load("assets/rf-16.mp3", "bg_music", 1); // load the sound files
	SoundManager::Instance()->load("assets/gamer-213.wav", "game_over", 0); // 1 for music
	SoundManager::Instance()->load("assets/noti-212.wav", "notification", 0);// 0 for .wav sounds
	SoundManager::Instance()->load("assets/woosh-89.wav", "woosh", 0);

	SoundManager::Instance()->playMusic("bg_music", 0, 5000);
	SoundManager::Instance()->playSound("woosh", -1, 0);
	SoundManager::Instance()->playSound("game_over", -1, 0);
	SoundManager::Instance()->playSound("notification", -1, 0);
	// NOTE: only 1 playMusic is allowed to play music, if multiple invoked - the last one plays

}

void Game::render() {
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: running = false; break;
			case SDL_KEYDOWN: {
				if (event.key.keysym.sym == SDLK_0) { // press 0 to increase volume
					SoundManager::Instance()->changeVolume(1);
					SoundManager::Instance()->changeVolumeSfx("woosh", 1);
				}
				if (event.key.keysym.sym == SDLK_9) { // press 9 to decrease volume
					SoundManager::Instance()->changeVolume(-1);
					SoundManager::Instance()->changeVolumeSfx("woosh", -1);
				}
				if (event.key.keysym.sym == SDLK_SPACE) { // pressing space, pauses and resumes the music
					SoundManager::Instance()->pauseOrPlay();
				}
				if (event.key.keysym.sym == SDLK_5) { // when you press 5, the music file starts from the 20th second
					SoundManager::Instance()->setMusicPosition(20.0);
				}
			}
			default: break;
		}
	}
}

void Game::update() {

}

void Game::clean() {
	std::cout << "cleaning game\n";
	Mix_CloseAudio(); // closes the mixer
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::isRunning() {
	return Game::running;
}

Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}

Game::~Game() {
	delete window;
	delete renderer;
}