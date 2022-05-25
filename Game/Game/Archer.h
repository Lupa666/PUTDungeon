#pragma once
#include "Player.h"
class Archer :
	public Player
{
public:
	Archer(int xPos, int yPos) :
		Player("assets/player.png", 0, 32, 32, 32, xPos, yPos, "stats/characters/archer.txt", 2)
	{}
};

