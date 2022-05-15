#include "Selector.h"

void Selector::setCoordinates(int x, int y)
{
	xpos = x;
	ypos = y;
}

void Selector::Update()
{
	//std::cout << destRect.x << " " << destRect.y << " " << destRect.w << " " << destRect.h << "\n";
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}