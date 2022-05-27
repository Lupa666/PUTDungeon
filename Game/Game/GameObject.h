#pragma once
#include "GameLoop.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y, int h, int w);
	GameObject(SDL_Texture *& text, int x, int y, int h, int w);
	~GameObject();

	virtual void Update();
	virtual void Render();

	int getX() {return xpos;}
	int getY() {return ypos;}
	void SetDest(int x, int y, int h, int w);
	protected :
		
	int xpos;
	int ypos;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};

