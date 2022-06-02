#pragma once
#include "GameLoop.h"
#include <iostream>
#include "Text.h"
#include "DynamicText.h"
#include "TextureLoader.h"
#include "GameObject.h"

#include "Player.h"
#include "Warrior.h"
#include "Archer.h"
#include "Mage.h"
#include "Thief.h"

#include "Enemy.h"
#include "Background.h"
#include "Menu.h"
#include "TileMap.h"
#include <cstdlib>
#include <algorithm>
#include "CombatManager.h"

#include "InventoryManagement.h"

Player* player;
Background *background;
Menu* startMenu;
TileMap* currentMap;
InventoryManagement* inventory;
GameObject* overScreen;
DynamicText* dungeonLevel;
SDL_Texture * enemyTexture;
SDL_Texture * itemTexture;
CombatManager * combat;

std::vector<Item> items;
std::vector<Enemy> enemies;

SDL_Renderer* GameLoop::renderer = nullptr;
SDL_Event GameLoop::event;

int GameLoop::floorLevel = 0;
GameState GameLoop::gameState = GameState::menu;

GameLoop::GameLoop() {}

GameLoop::~GameLoop() {}

void GameLoop::ResizeWindow()
{
	int *h = new int(640), *w = new int(800);
	SDL_GetWindowSize(window, w, h);
	SDL_SetWindowSize(window, *w, *h);
	SDL_RenderSetScale(renderer, (double)*w/(double)windowW, (double)*h/ (double)windowH);
	windowW = *w;
	windowH = *h;
	delete h, w;
}

void GameLoop::gameInit(const char* title, int xpos, int ypos, int width, int height) {

	windowW = width;
	windowH = height;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Game initialized\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_RESIZABLE);
		if (window) {
			std::cout << "Window created\n";
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
	dungeonLevel = new DynamicText("fonts/arcadeclassic.ttf", 24, ("current floor "+std::to_string(floorLevel)).c_str(), { 255, 255, 255, 255 });
	enemyTexture = TextureLoader::LoadText("assets/enemy.png");
	itemTexture = TextureLoader::LoadText("assets/item.png");
	currentMap = new TileMap();
}

void GameLoop::handleEvents() {

	SDL_PollEvent(&GameLoop::event);

	switch (GameLoop::gameState) {

	case GameState::menu: {
		switch (event.type) {
		case SDL_WINDOWEVENT:{
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED: {
				ResizeWindow();
			}
			}
		}
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
						switch (startMenu->getClassState()) {
						case ClassSelect::warrior : {
							player = new Warrior();
							break;
						}
						case ClassSelect::mage: {
							player = new Mage();
							break;
						}
						case ClassSelect::archer: {
							player = new Archer();
							break;
						}
						case ClassSelect::thief: {
							player = new Thief();
							break;
						}
						}
						generateFloor();
						player->SetPos(currentMap->startPosX, currentMap->startPosY);
						inventory = new InventoryManagement(player);
						combat = new CombatManager(player);
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
				player->MoveDown(currentMap->checkWallCollision(player->tileX, player->tileY + 1));
				break;
			}
			case SDLK_UP: {
				player->MoveUp(currentMap->checkWallCollision(player->tileX, player->tileY - 1));
				break;
			}
			case SDLK_LEFT: {
				player->MoveLeft(currentMap->checkWallCollision(player->tileX - 1, player->tileY));
				break;
			}
			case SDLK_RIGHT: {
				player->MoveRight(currentMap->checkWallCollision(player->tileX + 1, player->tileY));
				break;
			}
			case SDLK_i: {
				std::cout << "Opening inventory\n";
				gameState = GameState::inventory;
				break;
			}
			case SDLK_RETURN:{
				for (int i = 0; i < items.size(); i++)
				{
					if ((player->tileX == items[i].xPos) and (player->tileY == items[i].yPos)) {
						if (inventory->PickupItem(items[i])) {
							items.erase(items.begin() + i);
						}
						break;
					}
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
		break;
	}

	case GameState::combat: {
		switch (event.type) {
		case SDL_KEYDOWN: { //when key is pressed or held
			switch (GameLoop::event.key.keysym.sym) {
			case SDLK_DOWN: {
				combat->SelectDown();
				break;
			}
			case SDLK_UP: {
				combat->SelectUp();
				break;
			}
			case SDLK_LEFT: {
				combat->SelectLeft();
				break;
			}
			case SDLK_RIGHT: {
				combat->SelectRight();
				break;
			}
			case SDLK_ESCAPE: {
				combat->EndCombat();
				break;
			}
			case SDLK_RETURN: {
				combat->PressEnter();
				break;
			}
			}
			break;
		}
		}
		break;
	}
	case GameState::inventory: {
		switch (event.type) {
		case SDL_KEYDOWN: { //when key is pressed or held
			switch (GameLoop::event.key.keysym.sym) {
			case SDLK_DOWN: {
				inventory->MoveDown();
				break;
			}
			case SDLK_UP: {
				inventory->MoveUp();
				break;
			}
			case SDLK_LEFT: {
				inventory->DropItem();
				break;
			}
			case SDLK_RIGHT: {
				if (inventory->GetInventorySize()) {
					Item temp = inventory->GetCurrentItem();
					if (player->Equip(temp)) {
						inventory->DropItem();
					}
					else {
						inventory->ChangeCurrentItem(temp);
					}
				}
				break;
			}
			case SDLK_i: {
				inventory->ResetItemChoose();
				GameLoop::gameState = GameState::play;
				break;
			}
			case SDLK_ESCAPE: {
				GameLoop::gameState = GameState::play;
				break;
			}
			}
			break;
		}
		}
		break;
	}

	case GameState::over: {
		switch (event.type) {
		case SDL_KEYDOWN: { //when key is pressed or held
			isRunning = false;
		}
		}
		break;
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
		if (player->CurrentHealth < 1) {
			overScreen = new GameObject("Assets/over.png", 0, 0, 640, 800);
			overScreen->SetDest(0,0,640,800);
			gameState = GameState::over;
			overScreen->Update();
			break;
		}
		for (auto & it : items)
		{
			it.Update();
			if ((player->tileX == it.xPos) and (player->tileY == it.yPos)) {
				it.UpdateText();
			}
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i].Update();
			if (
				(enemies[i].tileX - 1 <= player->tileX and enemies[i].tileX + 1 >= player->tileX)
				and
				(enemies[i].tileY - 1 <= player->tileY and enemies[i].tileY + 1 >= player->tileY)
				) {
				combat->LoadEnemy(enemies[i]);
				gameState = GameState::combat;
				int itemRoll = rand() % 3;
				if (itemRoll >= 1) {
					int x, y;
					items.push_back(Item(itemTexture, enemies[i].tileX, enemies[i].tileY));
					(items.end() - 1)->onGround = true;
				}
				enemies.erase(enemies.begin()+i);
			}
		}
		if (player->tileX == currentMap->xEnd and player->tileY == currentMap->yEnd) {
			generateFloor();
			player->SetPos(currentMap->startPosX, currentMap->startPosY);
		}
		player->Update();
		break;
	}
	case GameState::combat: {
		if (player->CurrentHealth < 1) {
			overScreen = new GameObject("Assets/over.png", 0, 0, 640, 800);
			overScreen->SetDest(0, 0, 640, 800);
			gameState = GameState::over;
			overScreen->Update();
			break;
		}
		player->Update();
		player->SetDest(200, 200, 60, 60);
		combat->Update();
		break;
	}
	case GameState::inventory: {
		inventory->Update(30, 130);
		player->UpdateStatsText();
		break;
	}
	case GameState::over: {
		overScreen->Update();
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
		dungeonLevel->Render(30, 8);
		int n = 0;
		int spacing = 80;
		for (auto & enem : enemies)
		{
			enem.Render();
			n++;
		}
		for (auto & it : items)
		{
			if ((player->tileX == it.xPos) and (player->tileY == it.yPos)) {
				it.RenderText(450, 420);
				break;
			}
		}
		for (auto & it : items)
		{
			if (it.onGround) {
				it.Render();
			}
		}
		player->Render();
		break;
	}
	case GameState::combat: {
		combat->Render();
		player->Render();
		break;
	}
	case GameState::inventory: {
		inventory->Render(50, 50);
		player->RenderInventory(250, 50);
		player->RenderStats(400, 50);
		break;
	}
	case GameState::over: {
		overScreen->Render();
		break;
	}
	}
	SDL_RenderPresent(renderer);
}

void GameLoop::generateFloor()
{
	floorLevel++;
	int mapTemp = rand() % 9+1;
	std::string mapPath = "maps/map" + std::to_string(mapTemp) + ".txt";
	currentMap->LoadMap(mapPath.c_str());
	int size = rand() % 3+4;

	enemies.clear();
	for (int i = 0; i < size; i++) {
		int x, y;
		currentMap->GetNewEnemyPos(x, y);
		enemies.push_back(Enemy(enemyTexture, x, y));
	}

	items.clear();
	for (int i = 0; i < 4; i++) {
		int x, y;
		currentMap->GetNewEnemyPos(x, y);
		items.push_back(Item(itemTexture, x, y));
	}
	player->RegenFull();
	dungeonLevel->loadLabel(("current floor " + std::to_string(floorLevel)).c_str(), { 255, 255, 255, 255 });
	gameState = GameState::play;
}

void GameLoop::clean() {//cleans after closing the game
	delete player, background, startMenu, currentMap, inventory, overScreen, dungeonLevel, combat;
	SDL_DestroyTexture(enemyTexture);
	enemyTexture = nullptr;
	SDL_DestroyTexture(itemTexture);
	itemTexture = nullptr;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	std::cout << "Game cleaned\n";
}