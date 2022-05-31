#pragma once
#include "DynamicText.h"
#include "Selector.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"

class CombatManager
{
private:
	int choice = 0;
	DynamicText FIGHT;
	std::vector<Enemy> toFightEnemies;
	std::vector<DynamicText> playerActions;
public:
	CombatManager();
	~CombatManager();
	void LoadEnemy(Enemy);
	void ClearEnemies();
	bool NoEnemies();
	void EndCombat();
	void Update();
	void Render(int x = 0, int y = 0);
};

