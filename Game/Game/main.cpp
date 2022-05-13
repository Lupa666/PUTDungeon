#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "GameLoop.h"

GameLoop *game = nullptr;

int main(int argc, char *argv[]) {
	const short int framerate = 60;
	const int framedelay = 1000 / framerate;

	Uint32 frameStart;
	int frameTime;

	const int width = 800;
	const int height = 640;
	bool fullscreen = false;
	const char *title = "PutDungeon0.1v";

	game = new GameLoop();
	
	game->gameInit(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (framedelay > frameTime) {
			SDL_Delay(framedelay - frameTime);
		}
	}

	game->clean();
	return 0;
}