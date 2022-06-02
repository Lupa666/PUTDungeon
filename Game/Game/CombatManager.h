#pragma once
#include "DynamicText.h"
#include "Selector.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Selector.h"
#include "SoundPlayer.h"

class CombatManager
{
private:
	int choiceAction = 0;
	int choiceEnemy = 0;
	int actionsNumber = 0;
	bool enemyTurn = false;
	Selector *SelectAction, *SelectEnemy;
	DynamicText FIGHT;
	Player* toManagePlayer;
	DynamicText WATER, WIND, FIRE, EARTH;
	std::vector<Enemy> toFightEnemies;
	std::vector<DynamicText*> playerActions;
public:
	CombatManager(Player*);
	~CombatManager();
	void SelectUp();
	void SelectDown();
	void SelectLeft();
	void SelectRight();
	void LoadEnemy(Enemy);
	void ClearEnemies();
	bool NoEnemies();
	void EndCombat();
	void Update();
	void Render(int x = 0, int y = 0);

	void HurtPlayer();
	void PressEnter(SoundPlayer *);
	void CheckClearEnemies();
	void EnemyAction();
};

