#include "CombatManager.h"

CombatManager::CombatManager():
	FIGHT("fonts/arcadeclassic.ttf", 72, "COMBAT", { 255, 255, 255, 255 })
{
	playerActions.push_back(DynamicText("fonts/arcadeclassic.ttf", 24, "Actions", { 255, 255, 255, 255 }));
	playerActions.push_back(DynamicText("fonts/arcadeclassic.ttf", 24, "Attack Close", { 255, 255, 255, 255 }));
	playerActions.push_back(DynamicText("fonts/arcadeclassic.ttf", 24, "Attack Range", { 255, 255, 255, 255 }));
}

CombatManager::~CombatManager()
{

}



void CombatManager::LoadEnemy(Enemy t) {
	toFightEnemies.push_back(t);
}

void CombatManager::ClearEnemies()
{
	toFightEnemies.clear();
}

bool CombatManager::NoEnemies() {
	return	!(toFightEnemies.empty());
}

void CombatManager::EndCombat()
{
	choice = 0;
	toFightEnemies.clear();
}

void CombatManager::Update()
{
	int n = 0;
	int space = 100;
	std::cout << "\n";
	for (auto & i : toFightEnemies) {
		i.SetDest(400, 200+(space*n), 60, 60);
		n++;
		i.UpdateText();
	}
}

void CombatManager::Render(int x, int y)
{
	int n = 0;
	int space = 100;
	for (auto & i : toFightEnemies) {
		//i.SetDest(400, 200 + (space*n), 60, 60);
		i.Render();
		i.RenderText(480, 200 + (space*n));
		n++;
	}
	FIGHT.Render(112, 10);
}
