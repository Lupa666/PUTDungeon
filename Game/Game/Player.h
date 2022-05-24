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

	DynamicText *HP, *ST, *AMMO;

	int tileX;
	int tileY;

	Player(const char* texturesheet, int x, int y, int h, int w, int xStart = 1, int yStart = 1, const char* StatsPath = "stats/characters/warrior.txt") :
		GameObject(texturesheet, x, y, h, w), tileX(xStart), tileY(yStart)
	{
		std::ifstream stats;
		stats.open(StatsPath);
		while (!stats.eof()) {
			std::string temp;
			float x1;
			stats >> temp >> x1;
			PlayerStats.insert_or_assign(temp, x1);
		}
		stats.close();
		CurrentHealth = PlayerStats["health"];
		CurrentStamina = PlayerStats["stamina"];
		CurrentAmmo = PlayerStats["amunition"];

		HP = new DynamicText("fonts/arcadeclassic.ttf", 24, ("HP  " + std::to_string(CurrentHealth) + "  " + std::to_string((int)PlayerStats["health"])).c_str(), { 255, 255, 255, 255 });
		ST = new DynamicText("fonts/arcadeclassic.ttf", 24, ("ST  " + std::to_string(CurrentStamina) + "  " + std::to_string((int)PlayerStats["stamina"])).c_str(), { 255, 255, 255, 255 });
		AMMO = new DynamicText("fonts/arcadeclassic.ttf", 24, ("AMMO" + std::to_string(CurrentAmmo) + "  " + std::to_string((int)PlayerStats["amunition"])).c_str(), { 255, 255, 255, 255 });
	}
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

