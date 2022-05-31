#pragma once
#include "Player.h"
class Warrior :
	public Player
{
public:
	Warrior(int xPos = 0, int yPos = 0) :
		Player("assets/player.png", 32, 0, 32, 32, xPos, yPos, "stats/characters/warrior.txt", 0)
	{}

};

