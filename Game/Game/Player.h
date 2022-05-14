#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
	public:

	Player(const char* texturesheet, int x, int y, int h, int w) :
		GameObject(texturesheet, x, y, h, w) 
	{}

	void Update();
};

