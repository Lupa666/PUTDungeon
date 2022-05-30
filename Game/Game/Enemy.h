#pragma once
#include "GameObject.h"
#include "DynamicText.h"
#include <map>
#include <algorithm>

class Enemy :
	public GameObject
{
private:

	int enemyName;
	DynamicText *NAME, *HP, *STAMINA;

public:
	int currentHP;
	int tileX = 2;
	int tileY = 3;
	std::map<std::string, float> EnemyStats;


	Enemy(const char*, int, int);
	Enemy(SDL_Texture *&, int, int);
	~Enemy();
	void LoadStats();
	void SetText(int, int);
	void LoadTexture(const char*);
	void Update();
	void Render();
	void RenderText(int, int);
};

