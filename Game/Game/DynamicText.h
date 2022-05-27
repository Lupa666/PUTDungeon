#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class DynamicText
{
public:
	DynamicText(const char* font_path, int font_size, const char* msg_text, const SDL_Color &color);
	~DynamicText();
	void Render(int x, int y);

	void loadFont(const char* msg_text, const SDL_Color &color);

	SDL_Texture* text_texture = nullptr;

private:

	TTF_Font * font;
	std::string font_p;
	int font_s;
	SDL_Rect rectangle;

};
