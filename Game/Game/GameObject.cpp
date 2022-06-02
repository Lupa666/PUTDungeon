#include "GameObject.h"
#include "TextureLoader.h"
#include <iostream>

GameObject::GameObject(const char* texturesheet, int x, int y, int h, int w):
	xpos(x), ypos(y)
{
	srcRect.h = h;
	srcRect.w = w;
	srcRect.x = x;
	srcRect.y = y;
	objTexture = TextureLoader::LoadText(texturesheet);
}

GameObject::GameObject(SDL_Texture *& text, int x, int y, int h, int w):
	xpos(x), ypos(y)
{
	srcRect.h = h;
	srcRect.w = w;
	srcRect.x = x;
	srcRect.y = y;
	objTexture = text;
}

GameObject::~GameObject() {
}

void GameObject::Update()
{
}


void GameObject::Render()
{
	SDL_RenderCopy(GameLoop::renderer, objTexture, &srcRect, &destRect);
}

void GameObject::SetDest(int x, int y, int h, int w)
{
	destRect.x = x;
	destRect.y = y;
	destRect.h = h;
	destRect.w = w;
}