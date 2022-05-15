#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "TextureLoader.h"

enum class GameState { menu, play, inventory, combat, over };

class GameLoop
{
private:
	int count = 0;
	
	bool isRunning = false;
	SDL_Window *window = NULL;
	
public:
	GameLoop();
	~GameLoop();

	static GameState gameState;
	static SDL_Renderer *renderer;
	static SDL_Event event;

	void gameInit(const char*, int, int, int, int); //initializes game

	void handleEvents(); //handles events
	void update(); //updates game objects
	void render(); //renders a screen
	void clean(); //cleans screen

	const bool running() { return isRunning; }; //checks if game is running
};

