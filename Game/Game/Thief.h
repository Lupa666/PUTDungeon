#pragma once
#include "Player.h"
class Thief :
	public Player
{
public:
	Thief(int xPos, int yPos) :
		Player("assets/player.png", 32, 32, 32, 32, xPos, yPos, "stats/characters/rogue.txt", 3)
	{}
};

