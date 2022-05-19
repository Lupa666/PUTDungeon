#pragma once
#include "Player.h"
class Warrior :
	public Player
{
public:
	Warrior(int xPos, int yPos) :
		Player("assets/player.png", 32, 0, 32, 32, xPos, yPos)
	{}

};

