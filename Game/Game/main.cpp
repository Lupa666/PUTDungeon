#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "GameLoop.h"

GameLoop *game = nullptr;

int main(int argc, char *argv[]) {
	int width = 800;
	int height = 600;
	bool fullscreen = false;
	const char *title = "PutDungeon0.1v";

	game = new GameLoop();
	
	game->gameInit(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	return 0;
}