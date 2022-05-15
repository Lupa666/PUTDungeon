#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class Text
{
public:
	Text(const char* font_path, int font_size, const char* msg_text, const SDL_Color &color);

	void Render(int x, int y);

	static SDL_Texture *loadFont(const char* font_path, int font_size, const char*  msg_text, const SDL_Color &color);

private:
	SDL_Texture* text_texture = nullptr;
	SDL_Rect rectangle;

};

