#pragma once
#include "GameObject.h"
#include "TileMap.h"
class Player : public GameObject
{
	public:

	int tileX = 1;
	int tileY = 1;

	Player(const char* texturesheet, int x, int y, int h, int w) :
		GameObject(texturesheet, x, y, h, w) 
	{}

	void MoveUp(bool tileCheck = true);
	void MoveDown(bool tileCheck = true);
	void MoveLeft(bool tileCheck = true);
	void MoveRight(bool tileCheck = true);

	void Update();
};

