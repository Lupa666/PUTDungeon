#include "TextureLoader.h"

SDL_Texture * TextureLoader::LoadText(const char * filename, SDL_Renderer * ren)
{
	SDL_Surface* temp_surface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, temp_surface);
	SDL_FreeSurface(temp_surface);
	return texture;
}
