#pragma once
#include "GameObject.h"
#include <map>
#include <string>
#include <fstream>
#include "DynamicText.h"
#include "TileMap.h"
class Player : public GameObject
{
public:
	
	std::map<std::string, float> PlayerStats;
	int CurrentHealth;
	int CurrentStamina;
	int CurrentAmmo;
	static int playerClass;

	DynamicText *HP, *ST, *AMMO;

	int tileX;
	int tileY;


	Player(const char* texturesheet, int x, int y, int h, int w, int xStart, int yStart, const char* StatsPath, int pC);
	~Player();

	void MoveUp(bool tileCheck = true);
	void MoveDown(bool tileCheck = true);
	void MoveLeft(bool tileCheck = true);
	void MoveRight(bool tileCheck = true);
	void SetPos(int x, int y);
	virtual void Update();
	virtual void Render();
	virtual void Attack() {};
	virtual void PickUp() {};
};

