#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
	public:

	Player(const char* texturesheet, int x, int y, int h, int w) :
		GameObject(texturesheet, x, y, h, w) 
	{}

	void MoveLeft()		{xpos -= 32;}
	void MoveRight()	{xpos += 32;}
	void MoveUp()		{ypos -= 32;}
	void MoveDown()		{ypos += 32;}

	void Update();
};

