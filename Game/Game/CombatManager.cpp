#include "CombatManager.h"

CombatManager::CombatManager(Player* pl):
	FIGHT("fonts/arcadeclassic.ttf", 72, "COMBAT", { 255, 255, 255, 255 }),
	WATER("fonts/arcadeclassic.ttf", 24, "WATER", { 255, 255, 255, 255 }),
	WIND("fonts/arcadeclassic.ttf", 24, "WIND", { 255, 255, 255, 255 }),
	FIRE("fonts/arcadeclassic.ttf", 24, "FIRE", { 255, 255, 255, 255 }),
	EARTH("fonts/arcadeclassic.ttf", 24, "EARTH", { 255, 255, 255, 255 }),
	SelectAction(new Selector("assets/selector.png", 0, 0, 10, 10)),
	SelectEnemy(new Selector("assets/selector.png", 0, 0, 10, 10))
{
	toManagePlayer = pl;
	for (auto & act : toManagePlayer->CombatActions) {
		playerActions.push_back(new DynamicText("fonts/arcadeclassic.ttf", 24, act.c_str(), { 255, 255, 255, 255 }));
	}
	actionsNumber = playerActions.size();
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
	choiceAction--;
	if (choiceAction < 4 and choiceAction >= actionsNumber) {
		choiceAction = choiceAction + actionsNumber;
	}
	if (choiceAction < 0) {
		choiceAction = actionsNumber+3;
	}
	std::cout << choiceAction << "\n";
}

void CombatManager::SelectRight()
{
	choiceAction++;
	if (choiceAction < 4 and choiceAction >= actionsNumber) {
		choiceAction = choiceAction + actionsNumber;
	}
	if (choiceAction >= 8) {
		choiceAction = 0;
	}
	std::cout << choiceAction << "\n";
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
	for (auto & i : toFightEnemies) {
		i.SetDest(400, 200+(space*n), 60, 60);
		n++;
		i.UpdateText();
	}

	int ActionN = 0;
	if (choiceAction >= actionsNumber) {
		int temp = actionsNumber - 4;
		ActionN = temp + choiceAction;
	}
	else {
		ActionN = choiceAction;
	}
	int spaceEnemy = 100;
	int spaceAction = 70;
	SelectEnemy->setCoordinates(580, 200+(choiceEnemy*spaceEnemy));
	SelectAction->setCoordinates(200 + (ActionN*spaceAction), 580);
	SelectEnemy->Update();
	SelectAction->Update();
}

void CombatManager::Render(int x, int y)
{
	int n = 0;
	int space = 100;
	for (auto & i : toFightEnemies) {
		i.Render();
		i.RenderText(480, 200 + (space*n));
		n++;
	}
	n = 0;
	space = 70;
	for (auto & fg : playerActions) {
		fg->Render(200+(n*space), 550);
		n++;
	}
	WATER.Render(200 + (n * space), 550);
	n++;
	WIND.Render(200 + (n * space), 550);
	n++;
	FIRE.Render(200 + (n * space), 550);
	n++;
	EARTH.Render(200 + (n * space), 550);
	FIGHT.Render(112, 10);

	SelectEnemy->Render();
	SelectAction->Render();
}

void CombatManager::HurtPlayer()
{
	toManagePlayer->CurrentHealth -= 20;
}
