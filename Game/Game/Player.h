#pragma once
#include "GameObject.h"
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include "DynamicText.h"
#include "TileMap.h"


class Item : public GameObject {

public:
	std::string itemName;
	std::map<std::string, int> ItemStats;
	std::vector<DynamicText*> ItemText;
	DynamicText* name = nullptr;
	bool onGround;
	int xPos, yPos;

	Item(int x, int y); //rolls for random item
	~Item();
	void Render();
	void Update();
	void GenerateText();
	void RenderText(int xp, int yp);
};


class Player : public GameObject
{
public:
	
	std::map<std::string, float> PlayerStats;
	std::map<int, Item> EquippedItems;
	std::vector<DynamicText*> StatsText;
	std::string playerName;
	int CurrentHealth;
	int CurrentStamina;
	int CurrentAmmo;
	short int ElementalType[5] = { 1, 0, 0, 0, 0 };
	static int playerClass;

	DynamicText *HP, *ST, *AMMO, *NAME, *EQ;

	int tileX;
	int tileY;


	Player(const char* texturesheet, int x, int y, int h, int w, int xStart, int yStart, const char* StatsPath, int pC);
	~Player();
	void MoveUp(bool tileCheck = true);
	void MoveDown(bool tileCheck = true);
	void MoveLeft(bool tileCheck = true);
	void MoveRight(bool tileCheck = true);
	void SetPos(int x, int y);

	void RegenFull();
	bool Equip(Item&);
	void MakeStatsText();
	void PrintStats() {
		std::cout << "\n\n";
		for (auto st : PlayerStats) {
			std::cout << st.first << " " << st.second << "\n";
		}
	}
	virtual void Update();
	virtual void UpdateStatsText();
	virtual void Render();
	virtual void RenderInventory(int, int);
	virtual void RenderStats(int, int);
	virtual void Attack();
};

