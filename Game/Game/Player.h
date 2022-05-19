#pragma once
#include "GameObject.h"
#include "TileMap.h"
class Player : public GameObject
{
public:

	int tileX;
	int tileY;

	Player(const char* texturesheet, int x, int y, int h, int w, int xStart = 1, int yStart = 1) :
		GameObject(texturesheet, x, y, h, w), tileX(xStart), tileY(yStart)
	{
	}

	void MoveUp(bool tileCheck = true);
	void MoveDown(bool tileCheck = true);
	void MoveLeft(bool tileCheck = true);
	void MoveRight(bool tileCheck = true);
	void SetPos(int x, int y);
	void Update();
	virtual void Attack() {};
};

