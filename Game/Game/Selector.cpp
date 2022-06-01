#include "Selector.h"

void Selector::setCoordinates(int x, int y)
{
	xpos = x;
	ypos = y;
}

void Selector::Update()
{
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}