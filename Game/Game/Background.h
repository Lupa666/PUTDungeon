#pragma once
#include "GameObject.h"
class Background :
	public GameObject
{
public:
	Background(const char* texturesheet, int x, int y, int h, int w) :
		GameObject(texturesheet, x, y, h, w) {}
	void Update();
};

