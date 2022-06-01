#pragma once
#include "Player.h"
class Warrior :
	public Player
{
private:
	void LoadCombatActions();
public:
	Warrior(int xPos = 0, int yPos = 0) :
		Player("assets/player.png", 32, 0, 32, 32, xPos, yPos, "stats/characters/warrior.txt", 0)
	{
		LoadCombatActions();
	}
	void TakeDamage(int dmg);
	int MeleeAttack();
	int RangeAttack();
	int ElementalAttack();
	int CutAttack();
	int CrushAttack();
};

