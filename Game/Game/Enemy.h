#pragma once
#include "GameObject.h"
#include "DynamicText.h"
#include <map>
#include <algorithm>

class Enemy :
	public GameObject
{
private:

	std::string enemyName;
	DynamicText NAME, HP, STAMINA;

public:
	int currentHP;
	int currentStamina;
	int tileX = 2;
	int tileY = 3;
	std::map<std::string, float> EnemyStats;


	Enemy(const char*, int, int);
	Enemy(SDL_Texture *&, int, int);
	~Enemy();
	void LoadStats();
	void LoadTexture(const char*);
	void Update();
	void UpdateText();
	void Render();
	void RenderText(int, int);
};

