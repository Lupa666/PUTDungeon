#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Player.h"
#include "DynamicText.h"
#include "TileMap.h"

class Item: public GameObject{

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

class InventoryManagement
{
private:
	Player *toManage;
	std::vector<Item> InventoryItems;
	DynamicText *Inv = new DynamicText("fonts/arcadeclassic.ttf", 32, "INVENTORY", { 255, 255, 255, 255 });
	int MaxSize = 4, CurrentSize = 0;
public:
	InventoryManagement(Player*);
	~InventoryManagement();

	bool PickupItem(Item& toPickup);
	void DropItem();

	void Render(int, int);
};

