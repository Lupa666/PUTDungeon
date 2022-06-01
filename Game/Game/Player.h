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
	std::vector<std::shared_ptr<DynamicText>> ItemText;
	DynamicText* name = nullptr;
	bool onGround;
	int xPos, yPos;

	Item(SDL_Texture *&, int, int); //rolls for random item
	Item(int, int); //rolls for random item
	~Item();
	void Render();
	void UpdateText();
	void Update();
	void GenerateText();
	void RenderText(int xp, int yp);
};


class Player : public GameObject
{
public:
	std::vector<std::string> CombatActions;
	std::map<std::string, float> PlayerStats;
	std::map<int, Item> EquippedItems;
	std::vector<std::shared_ptr<DynamicText>> StatsText;
	std::string playerName;
	int CurrentHealth;
	int CurrentStamina;
	int CurrentAmmo;
	short int ElementalType[5] = { 1, 0, 0, 0, 0 }; //normal, water, wind, fire, earth
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

	void RegenRound();
	void RegenFight();
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
	virtual void RenderMinStats(int, int);
	virtual void Render(int x = 16, int y = 440, bool renderMinStats = true);
	virtual void RenderInventory(int, int);
	virtual void RenderStats(int, int);

	virtual void LoadCombatActions() {}

	virtual void TakeDamage(int dmg) {}
	virtual int MeleeAttack() { return 0; }
	virtual int RangeAttack() { return 0; }
	virtual int ElementalAttack() { return 0; }
	virtual int CutAttack() { return 0; }
	virtual int CrushAttack() { return 0; }
};

