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
		choiceAction = choiceAction - 4 + actionsNumber;
	}
	if (choiceAction < 0) {
		choiceAction = 7;
	}
}

void CombatManager::SelectRight()
{
	choiceAction++;
	if (choiceAction < 4 and choiceAction >= actionsNumber) {
		choiceAction = choiceAction + 4 - actionsNumber;
	}
	if (choiceAction >= 8) {
		choiceAction = 0;
	}
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
	GameLoop::gameState = GameState::play;
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
	SelectEnemy->setCoordinates(380, 200+(choiceEnemy*spaceEnemy));
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

void CombatManager::PressEnter(SoundPlayer * audio)
{
	enemyTurn = false;
	int ToDealDamage = 0;
	int Element = 0;
	switch (choiceAction) {
	case 0: {
		ToDealDamage = toManagePlayer->MeleeAttack();
		break;
	}
	case 1: {
		ToDealDamage = toManagePlayer->RangeAttack();
		break;
	}
	case 2: {
		ToDealDamage = toManagePlayer->CutAttack();
		break;
	}
	case 3: {
		ToDealDamage = toManagePlayer->CrushAttack();
		break;
	}
	case 4: {
		if (toManagePlayer->ElementalType[1]) {
			Element = 1;
			ToDealDamage = toManagePlayer->ElementalAttack();
		}
		break;
	}
	case 5: {
		if (toManagePlayer->ElementalType[2]) {
			Element = 2;
			ToDealDamage = toManagePlayer->ElementalAttack();
		}
		break;
	}
	case 6: {
		if (toManagePlayer->ElementalType[3]) {
			Element = 3;
			ToDealDamage = toManagePlayer->ElementalAttack();
		}
		break;
	}
	case 7: {
		if (toManagePlayer->ElementalType[4]) {
			Element = 4;
			ToDealDamage = toManagePlayer->ElementalAttack();
		}
		break;
	}
	} //chooses what action to make
	if (ToDealDamage) {
		std::cout << "Player attacked for: " << ToDealDamage << " With element:" << Element << "\n";
		toFightEnemies[choiceEnemy].TakeDamage(ToDealDamage,Element);
		CheckClearEnemies();
		enemyTurn = true;
		if (ToDealDamage >= 140) {
			audio->PlayHitHard();
		}
		else {
			audio->PlayHitNormal();
		}
	}
	else {
		std::cout << "Couldn't take action!" << "\n";
	}
	if (!NoEnemies()) {
		EndCombat();
		return;
	}
	if (enemyTurn) {
		EnemyAction();
		toManagePlayer->RegenRound();
		enemyTurn = false;
	}
}

void CombatManager::CheckClearEnemies()
{
	for (int i = 0; i < toFightEnemies.size(); i++) {
		if (toFightEnemies[i].currentHP < 1) {
			toFightEnemies.erase(toFightEnemies.begin()+i);
			i--;
		}
	}
}

void CombatManager::EnemyAction()
{
	//temporary
	for (int i = 0; i < toFightEnemies.size(); i++) {
		bool SuccesfullAttack = false;
		int damage = 0;
		while (!SuccesfullAttack) {
			int temp = rand() % 5;
			if (temp == 4) {
				damage = toFightEnemies[i].Attack();
			}
			else {
				damage = toFightEnemies[i].SpecialAttack();
			}
			if (damage != 0) {
				SuccesfullAttack = true;
			}
		}
		std::cout << "Player got attacked for: " << damage << " damage!\n";
		toManagePlayer->TakeDamage(damage);
	}	
}
