#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "GameLoop.h"
#include <cstdlib>
#include <ctime>


int main(int argc, char *argv[]) {
	GameLoop *game = nullptr;

	const short int framerate = 60;
	const int framedelay = 1000 / framerate;

	Uint32 frameStart;
	int frameTime;

	const int width = 800;
	const int height = 640;
	bool fullscreen = false;
	const char *title = "PuutDungeon v0.9";

	game = new GameLoop();
	
	TTF_Init();
	srand(time(NULL));

	game->gameInit(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);

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