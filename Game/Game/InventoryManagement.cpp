#include "InventoryManagement.h"

InventoryManagement::InventoryManagement(Player * pl)
{
	toManage = pl;
}

InventoryManagement::~InventoryManagement()
{
}

bool InventoryManagement::PickupItem(Item &toPickup)
{
	if (CurrentSize == MaxSize) {
		return false;
	}
	else {
		toPickup.onGround = false;
		CurrentSize++;
		InventoryItems.push_back(toPickup);
	}
	return true;
}

void InventoryManagement::Render(int xp, int yp)
{
	Inv->Render(xp, yp);
	int n = 0;
	int spacing = 20;
	for (auto & it : InventoryItems)
	{
		n++;
		it.RenderText(xp+10, yp+(120*n));
	}
}


Item::Item(int x = 1, int y = 1):
	GameObject("assets/item.png", 0, 0, 32, 32)
{
	xPos = x;
	yPos = y;
	std::cout << "Rolling item\n";
	int ItemRarity = rand()%(100 +(GameLoop::floorLevel + GameLoop::floorLevel*7));
	std::ifstream fileStats;
	std::string filePath = "stats/items/";
	if (ItemRarity < 70) { //common
		filePath += "common/";
		int tempRand = rand() % 4;
		switch (tempRand) {
		case 0: {
			filePath += "amulet";
			break;
		}
		case 1: {
			filePath += "boots";
			break;
		}
		case 2: {
			filePath += "chest";
			break;
		}
		case 3: {
			filePath += "ring";
			break;
		}
		}
		tempRand = rand() % 4;
		switch (tempRand) {
		case 0: {
			filePath += "erth";
			break;
		}
		case 1: {
			filePath += "fire";
			break;
		}
		case 2: {
			filePath += "wate";
			break;
		}
		case 3: {
			filePath += "wind";
			break;
		}
		}
	}
	else {
		if (ItemRarity < 80) { //green
			filePath += "green/";
		}
		else if (ItemRarity < 90) { //blue
			filePath += "blue/";
		}
		else if (ItemRarity < 100) { //red
			filePath += "red/";
		}
		else if (ItemRarity < 110) { //black
			filePath += "black/";
		}
		else { //rainbow
			filePath += "rainbow/";
		}
		switch (Player::playerClass) {
		case 0: {
			bool sworsh = rand() % 2;
			if (sworsh) {
				filePath += "sword";
			}
			else {
				filePath += "shield";
			}
			break;
		}
		case 1: {
			filePath += "staff";
			break;
		}
		case 2: {
			filePath += "bow";
			break;
		}
		case 3: {
			filePath += "daggers";
			break;
		}
		}

	}
	filePath += ".txt";
	std::cout << filePath << "\n";
	fileStats.open(filePath);
	std::string tempKey;
	std::string ItemName;
	fileStats >> tempKey >> ItemName;
	std::cout << tempKey << " " << ItemName << "\n";
	name = new DynamicText("fonts/arcadeclassic.ttf", 20, (tempKey+" "+ItemName).c_str(), { 255, 255, 255, 255 });
	while (!fileStats.eof()) {
		float tempStats;
		fileStats >> tempKey >> tempStats;
		ItemStats.try_emplace(tempKey, tempStats);
	}
	fileStats.close();

	GenerateText();
}

Item::~Item()
{
}

void Item::Render()
{
	if (onGround) {
		GameObject::Render();
	}
}

void Item::GenerateText()
{
	for (auto x : ItemStats)
	{
		if (x.first == "type" or x.first == "item") {
			continue;
		}else {
			std::string temp = x.first + " " + std::to_string(x.second);
			std::cout << temp << "\n";
			ItemText.push_back(new DynamicText("fonts/arcadeclassic.ttf", 20, temp.c_str(), { 255, 255, 255, 255 }));
		}	
	}
}

void Item::RenderText(int xp, int yp)
{
	
	int spacing = 20, n = 0;
	name->Render(xp, yp + (spacing*n));
	n++;
	for (auto x : ItemText)
	{
		x->Render(xp, yp+(spacing*n));
		n++;
	}
}

void Item::Update()
{
	destRect.x = TileMap::getTilePosX(xPos);
	destRect.y = TileMap::getTilePosY(yPos);
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}
