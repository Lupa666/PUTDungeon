#include "InventoryManagement.h"

InventoryManagement::InventoryManagement(Player * pl)
{
	toManage = pl;
}

InventoryManagement::~InventoryManagement()
{
}


Item::Item(const char* texturePath):
	GameObject(texturePath, 0, 0, 32, 32)
{
	int ItemRarity = rand()%100 + (16 * (GameLoop::floorLevel-1));
	std::ofstream fileStats;
	std::string filePath = "items/";
	if (ItemRarity < 50) {
		filePath += "common/";
	}
	else if (ItemRarity < 70) {

	}
	fileStats.open(filePath);
	//insert stats
	fileStats.close();
}

Item::~Item()
{
}

void Item::Render()
{
}

void Item::Update()
{
}
