#pragma once
#include "Player.h"
class Mage :
	public Player
{
public:
	Mage(int xPos = 0, int yPos = 0) :
		Player("assets/player.png", 0, 0, 32, 32, xPos, yPos, "stats/characters/mage.txt", 1)
	{}
};

