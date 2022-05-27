#include "InventoryManagement.h"

InventoryManagement::InventoryManagement(Player * pl):
	sel("assets/selector.png", 0, 0, 10, 10)
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

void InventoryManagement::DropItem()
{
	if (!InventoryItems.empty()) {
		InventoryItems.erase(InventoryItems.begin() + itemChoose);
		CurrentSize--;
		MoveUp();
	}
}

void InventoryManagement::Equip()
{
}

void InventoryManagement::MoveUp()
{
	if (!InventoryItems.empty()) {
		itemChoose = (itemChoose - 1);
		if (itemChoose < 0) { itemChoose = InventoryItems.size()-1; }
	}
}

void InventoryManagement::MoveDown()
{
	if (!InventoryItems.empty()) {
		itemChoose = (itemChoose + 1);
		if (itemChoose >= InventoryItems.size()) { itemChoose = 0; }
	}
}

Item InventoryManagement::GetCurrentItem()
{
	return InventoryItems[itemChoose];
}

void InventoryManagement::ChangeCurrentItem(Item &toChange)
{
	InventoryItems[itemChoose] = toChange;
}

void InventoryManagement::Update(int xp, int yp)
{
	if (!InventoryItems.empty()) {

		int spacing = 20;
		sel.setCoordinates(xp, yp + (80 * itemChoose));
		sel.Update();
	}
}

void InventoryManagement::Render(int xp, int yp)
{
	Inv->Render(xp, yp);
	if (!InventoryItems.empty()) {
		sel.Render();
		int n = 0;
		int spacing = 20;
		for (auto & it : InventoryItems)
		{
			n++;
			it.RenderText(xp + 10, yp + (80 * n));
		}
	}
}


