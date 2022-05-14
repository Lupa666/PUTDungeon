#pragma once
#include <iostream>
#include "GameLoop.h"
#include "TextureLoader.h"
#include "GameObject.h"
#include "Player.h"
#include "Background.h"

Player* player;
Background *background;

SDL_Renderer* GameLoop::renderer = nullptr;
SDL_Event GameLoop::event;

GameState GameLoop::gameState = GameState::menu;

GameLoop::GameLoop() {}

GameLoop::~GameLoop() {}

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

	background = new Background("assets/bckg.png", 0, 0,height,width);
	
}

void GameLoop::handleEvents() {

	SDL_PollEvent(&GameLoop::event);
	switch (event.type) {
	case SDL_QUIT: { //when pressing x on the window - quits the game
		isRunning = false;
		break;
	}
	case SDL_KEYDOWN: { //when key raises          ONLY FOR TESTING
		switch (GameLoop::event.key.keysym.sym) {
		case SDLK_RETURN: {
			gameState = GameState::play;
			player = new Player("assets/player.png", 0, 0, 32, 32);
			break;
		}
		case SDLK_DOWN: {
			if (gameState == GameState::play) {
				std::cout << "Ruch!";
				//player->MoveDown();
			}
			break;
		}
		case SDLK_UP: {
			if (gameState == GameState::play) {
				std::cout << "Ruch!";
				//player->MoveUp();
			}
			break;
		}
		case SDLK_LEFT: {
			if (gameState == GameState::play) {
				std::cout << "Ruch!";
				//player->MoveDown();
			}
			break;
		}
		case SDLK_RIGHT: {
			if (gameState == GameState::play) {
				std::cout << "Ruch!";
				//player->MoveRight();
			}
			break;
		}
		}
	}
	default: {
		break;
		}
	}
	}

void GameLoop::update() 
{
	background->Update();
	if (gameState == GameState::play) {
		player->Update();
	}
}

void GameLoop::render() {
	SDL_RenderClear(renderer);
	background->Render();

	//add things to render
	if (gameState == GameState::play) {
		player->Render();
	}

	SDL_RenderPresent(renderer);
}

void GameLoop::clean() {//cleans after closing the game
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned\n";
}