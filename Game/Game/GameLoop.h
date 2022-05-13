#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureLoader.h"

class GameLoop
{
private:
	int count = 0;
	bool isRunning = false;
	SDL_Window *window = NULL;
	
public:
	GameLoop();
	~GameLoop();

	static SDL_Renderer *renderer;

	void gameInit(const char*, int, int, int, int, bool); //initializes game

	void handleEvents(); //handles events
	void update(); //updates game objects
	void render(); //renders a screen
	void clean(); //cleans screen

	const bool running() { return isRunning; }; //checks if game is running
};

