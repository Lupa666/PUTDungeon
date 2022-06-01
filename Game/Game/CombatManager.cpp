#include "CombatManager.h"

CombatManager::CombatManager(Player* pl):
	FIGHT("fonts/arcadeclassic.ttf", 72, "COMBAT", { 255, 255, 255, 255 }),
	WATER("fonts/arcadeclassic.ttf", 24, "WATER", { 255, 255, 255, 255 }),
	WIND("fonts/arcadeclassic.ttf", 24, "WIND", { 255, 255, 255, 255 }),
	FIRE("fonts/arcadeclassic.ttf", 24, "FIRE", { 255, 255, 255, 255 }),
	EARTH("fonts/arcadeclassic.ttf", 24, "EARTH", { 255, 255, 255, 255 }),
	SelectAction("assets/selector.png", 0, 0, 10, 10),
	SelectEnemy("assets/selector.png", 0, 0, 10, 10)
{
	toManagePlayer = pl;
	playerActions.push_back(DynamicText("fonts/arcadeclassic.ttf", 24, "Actions", { 255, 255, 255, 255 }));
	playerActions.push_back(DynamicText("fonts/arcadeclassic.ttf", 24, "Attack Close", { 255, 255, 255, 255 }));
	playerActions.push_back(DynamicText("fonts/arcadeclassic.ttf", 24, "Attack Range", { 255, 255, 255, 255 }));
}

CombatManager::~CombatManager()
{

}

void CombatManager::SelectUp()
{
	choiceEnemy--;
	if (choiceEnemy < 0) {
		choiceEnemy = toFightEnemies.size()-1;
	}
}

void CombatManager::SelectDown()
{
	choiceEnemy++;
	if (choiceEnemy >= toFightEnemies.size()) {
		choiceEnemy = 0;
	}
}

void CombatManager::SelectLeft()
{
	/*choiceEnemy--;
	if (choiceEnemy < 0) {
		choiceEnemy = toFightEnemies.size() - 1;
	}*/
}

void CombatManager::SelectRight()
{
	/*choiceEnemy++;
	if (choiceEnemy >= toFightEnemies.size()) {
		choiceEnemy = 0;
	}*/
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
	choiceAction = 0;
	choiceEnemy = 0;
	toFightEnemies.clear();
	toManagePlayer->RegenFight();
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
	WATER.Render(400, 500);
	WIND.Render(480, 500);
	FIRE.Render(560, 500);
	EARTH.Render(620, 500);
	FIGHT.Render(112, 10);
}

void CombatManager::HurtPlayer()
{
	toManagePlayer->CurrentHealth -= 20;
}
