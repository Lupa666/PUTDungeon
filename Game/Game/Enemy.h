#pragma once
#include "GameObject.h"


class Enemy :
	public GameObject
{
private:

	int health = 10;
	int attackPower = 3;

public:
	int tileX = 2;
	int tileY = 3;
	int counter = 0;

	Enemy(const char*, int, int);
	Enemy(SDL_Texture *&, int, int);
	~Enemy();
	void LoadTexture(const char*);
	void Update();
	void Render();
};

