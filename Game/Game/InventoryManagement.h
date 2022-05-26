#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Player.h"
#include "DynamicText.h"
#include "Selector.h"
#include "TileMap.h"

class InventoryManagement
{
private:
	Player *toManage;
	std::vector<Item> InventoryItems;
	Selector sel;
	int itemChoose = 0;
	DynamicText *Inv = new DynamicText("fonts/arcadeclassic.ttf", 32, "INVENTORY", { 255, 255, 255, 255 });
	short int MaxSize = 4, CurrentSize = 0;
public:
	InventoryManagement(Player*);
	~InventoryManagement();

	bool PickupItem(Item& toPickup);
	void DropItem();
	void Equip();

	void ResetItemChoose() { itemChoose = 0; }
	void MoveUp();
	void MoveDown();
	int GetInventorySize() { return CurrentSize; }
	Item GetCurrentItem();
	void ChangeCurrentItem(Item);
	void Update(int, int);
	void Render(int, int);
};

