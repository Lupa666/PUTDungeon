#pragma once
#include <iostream>
#include "Text.h"
#include "GameLoop.h"
#include "TextureLoader.h"
#include "GameObject.h"
#include "Player.h"
#include "Background.h"
#include "Menu.h"

Player* player;
Background *background;
Menu* startMenu;

SDL_Renderer* GameLoop::renderer = nullptr;
SDL_Event GameLoop::event;

GameState GameLoop::gameState = GameState::menu;

GameLoop::GameLoop() {}

GameLoop::~GameLoop() {}

void GameLoop::gameInit(const char* title, int xpos, int ypos, int width, int height) {

	

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Game initialized\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
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
	startMenu = new Menu(24, "fonts/arcadeclassic.ttf", {255, 255, 255, 255}, 50, 200);
}

void GameLoop::handleEvents() {

	SDL_PollEvent(&GameLoop::event);

	switch (GameLoop::gameState) {
	case GameState::menu: {
		switch (event.type) {
		case SDL_KEYDOWN: {
			switch (GameLoop::event.key.keysym.sym) {
			case SDLK_RETURN: {
				player = new Player("assets/player.png", 0, 0, 32, 32);
				gameState = GameState::play;
				break;
			}
			}
			break;
		}
		}
		break;
	}
	case GameState::play: {
		switch (event.type) {
		case SDL_KEYDOWN: { //when key is pressed or held
			switch (GameLoop::event.key.keysym.sym) {
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
			break;
		}
		}
	}
	case GameState::combat: {

	}
	case GameState::inventory: {

	}
	case GameState::over: {

	}
	}
	if (event.type == SDL_QUIT) {
		isRunning = false;
	}

	}

void GameLoop::update()
{
	background->Update();

	switch (GameLoop::gameState) {
	case GameState::menu : {
		//startMenu->Update();
		break;
	}
	case GameState::play : {
		player->Update();
		break;
	}
	case GameState::combat: {
		break;
	}
	case GameState::inventory: {
		break;
	}
	case GameState::over: {
		break;
	}
	}
}

void GameLoop::render() {
	SDL_RenderClear(renderer);
	background->Render();

	//add things to render
	switch (GameLoop::gameState) {
	case GameState::menu: {
		startMenu->Render();
		break;
	}
	case GameState::play: {
		player->Render();
	}
	case GameState::combat: {

	}
	case GameState::inventory: {

	}
	case GameState::over: {

	}
	}

	SDL_RenderPresent(renderer);
}

void GameLoop::clean() {//cleans after closing the game
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
	std::cout << "Game cleaned\n";
}