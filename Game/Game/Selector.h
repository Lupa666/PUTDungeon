#pragma once
#include "GameObject.h"

class Selector : public GameObject
{
public:
	Selector(const char* texturesheet, int x, int y, int h, int w) :
		GameObject(texturesheet, x, y, h, w)
	{}

	void setCoordinates(int x, int y);
	void Update();
};
