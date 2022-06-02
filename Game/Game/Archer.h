#pragma once
#include "Player.h"
class Archer :
	public Player
{
private:
	void LoadCombatActions();
public:
	Archer(int xPos = 0, int yPos = 0) :
		Player("assets/player.png", 0, 32, 32, 32, xPos, yPos, "stats/characters/archer.txt", 2)
	{
		LoadCombatActions();
	}

	void TakeDamage(int dmg);
	int MeleeAttack();
	int RangeAttack();
	int ElementalAttack();
};

