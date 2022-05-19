#pragma once
#include "GameLoop.h"
#include <iostream>
#include "Text.h"
#include "TextureLoader.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Menu.h"
#include "TileMap.h"
#include <cstdlib>

Player* player;
Background *background;
Menu* startMenu;
TileMap* currentMap;
std::vector<Enemy> enemies;

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
			case SDLK_DOWN: {
				startMenu->MoveDown();
				break;
			}
			case SDLK_UP: {
				startMenu->MoveUp();
				break;
			}
			case SDLK_LEFT: {
				if (startMenu->getStartSelect() or startMenu->getAuthorDisplay()) {
					startMenu->ResetState();
				}
				break;
			}
			case SDLK_RETURN: {
				switch (startMenu->getMenuState()) {
				case MenuSelect::start: {
					if (startMenu->getStartSelect()) {
						generateFloor();
						switch (startMenu->getClassState()) {
						case ClassSelect::warrior : {
							player = new Player("assets/player.png", 0, 0, 32, 32, currentMap->startPosX, currentMap->startPosY);
							break;
						}
						case ClassSelect::mage: {
							player = new Player("assets/player.png", 0, 0, 32, 32, currentMap->startPosX, currentMap->startPosY);
							break;
						}
						case ClassSelect::archer: {
							player = new Player("assets/player.png", 0, 0, 32, 32, currentMap->startPosX, currentMap->startPosY);
							break;
						}
						case ClassSelect::thief: {
							player = new Player("assets/player.png", 0, 0, 32, 32, currentMap->startPosX, currentMap->startPosY);
							break;
						}
						}
						delete startMenu;
					}
					else {
						startMenu->PressStart();
					}
					break;
				}
				case MenuSelect::authors: {
					startMenu -> PressAuthors();
					break;
				}
				
				case MenuSelect::quit: {
					isRunning = false;
					break;
				}
				}
				break;
			}
			}
			break;
		}
		}
		break;
	}


	case GameState::play: {
		//player input
		switch (event.type) {
		case SDL_KEYDOWN: { //when key is pressed or held
			switch (GameLoop::event.key.keysym.sym) {
			case SDLK_DOWN: {
				if (gameState == GameState::play) {
					player->MoveDown(currentMap->checkWallCollision(player->tileX, player->tileY + 1));
				}
				break;
			}
			case SDLK_UP: {
				if (gameState == GameState::play) {
					player->MoveUp(currentMap->checkWallCollision(player->tileX, player->tileY - 1));
				}
				break;
			}
			case SDLK_LEFT: {
				if (gameState == GameState::play) {
					player->MoveLeft(currentMap->checkWallCollision(player->tileX - 1, player->tileY));
				}
				break;
			}
			case SDLK_RIGHT: {
				if (gameState == GameState::play) {
					player->MoveRight(currentMap->checkWallCollision(player->tileX + 1, player->tileY));
				}
				break;
			}
			case SDLK_ESCAPE: {
				delete player;
				floorLevel = 0;
				startMenu = new Menu(24, "fonts/arcadeclassic.ttf", { 255, 255, 255, 255 }, 50, 200);
				gameState = GameState::menu;
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
		startMenu->Update();
		break;
	}
	case GameState::play : {
		for (auto & enem : enemies)
		{
			if (
				(enem.tileX - 1 <= player->tileX and enem.tileX + 1 >= player->tileX)
				and
				(enem.tileY - 1 <= player->tileY and enem.tileY + 1 >= player->tileY)
				) {
				std::cout << "PREPARE TO FIGHT!\n";
			}

			enem.Update();
		}
		if (player->tileX == currentMap->xEnd and player->tileY == currentMap->yEnd) {
			generateFloor();
			player->SetPos(currentMap->startPosX, currentMap->startPosY);
		}
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
		currentMap->Render();
		player->Render();
		for (auto & enem : enemies)
		{
			enem.Render();
		}
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

	SDL_RenderPresent(renderer);
}

void GameLoop::generateFloor()
{
	floorLevel++;
	currentMap = new TileMap(12, 32);
	int mapTemp = rand() % 5+1;
	std::string mapPath = "maps/map" + std::to_string(mapTemp) + ".txt";
	currentMap->LoadMap(mapPath.c_str());
	int size = rand() % 3 + 5;
	enemies.clear();
	for (int i = 0; i < size; i++) {
		int x, y;
		currentMap->GetNewEnemyPos(x, y);
		enemies.push_back(Enemy("assets/enemy.png", x, y));
	}
	gameState = GameState::play;
}

void GameLoop::clean() {//cleans after closing the game
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	std::cout << "Game cleaned\n";
}