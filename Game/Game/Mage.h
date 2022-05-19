#pragma once
#include "Player.h"
class Mage :
	public Player
{
public:
	Mage(int xPos, int yPos) :
		Player("assets/player.png", 0, 0, 32, 32, xPos, yPos)
	{}
};

