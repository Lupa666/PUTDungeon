#pragma once

#include "GameLoop.h"

class TextureLoader
{
public:
	static SDL_Texture* LoadText(const char* filename);
};

