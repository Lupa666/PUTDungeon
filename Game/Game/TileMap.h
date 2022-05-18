#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include "TextureLoader.h"
#include "GameObject.h"

//0 - wall, 1 - ground

class Tile
{
private:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
public:
	Tile(const char* texturesheet, int h, int w);
	~Tile();

	void Render(int x, int y);
};

class TileMap
{
private:
	int MapArea[20][12];
	Tile *tiles[3];

	int xStart = 0, yStart = 32;
	int size = 32;

public:
	TileMap(int, int);
	~TileMap();

	void LoadMap(const char*);
	void Update();
	void Render();
};

