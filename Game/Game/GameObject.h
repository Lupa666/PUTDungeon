#pragma once
#include "GameLoop.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y, int h, int w);
	~GameObject();

	virtual void Update();
	virtual void Render();

	int getX() {return xpos;}
	int getY() {return ypos;}

	protected :

	int xpos;
	int ypos;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};

