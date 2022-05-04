#include "GameLoop.h"

GameLoop::GameLoop() {

}

GameLoop::~GameLoop() {

}

void GameLoop::gameInit(const char* title, int xpos, int ypos, int width, int height, bool fullscreen = false) {

	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Game initialized\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created\n";
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!\n";
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

}

void GameLoop::handleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT: { //when pressing x on the window - quits the game
		isRunning = false;
		break;
	}
	default: {
		break;
	}
	}
}

void GameLoop::update() {
	count++;
	std::cout << count << " ";
}

void GameLoop::render() {
	SDL_RenderClear(renderer);
	//add things to render
	SDL_RenderPresent(renderer);
}

void GameLoop::clean() {//cleans after closing the game
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned\n";
}