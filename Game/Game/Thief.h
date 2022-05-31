#pragma once
#include "Player.h"
class Thief :
	public Player
{
public:
	Thief(int xPos = 0, int yPos = 0) :
		Player("assets/player.png", 32, 32, 32, 32, xPos, yPos, "stats/characters/rogue.txt", 3)
	{}
};

