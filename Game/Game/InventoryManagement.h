#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Player.h"

class Item: public GameObject{

public:
	std::string itemName;
	std::map<std::string, int> ItemStats;
	int rarity;

	int xPos, yPos;

	Item(const char*);
	~Item();
	void Render();
	void Update();
};

class InventoryManagement
{
private:
	Player *toManage;
	int MaxSize = 8;
	int currentSelect = 0;
public:
	InventoryManagement(Player*);
	~InventoryManagement();
	void PickupItem();
	void DropItem();
};

