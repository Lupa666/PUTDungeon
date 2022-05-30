#include "DynamicText.h"
#include <iostream>
#include "GameLoop.h"

DynamicText::DynamicText(const char* font_path, int font_size, const char* msg_text, const SDL_Color &color) {
	
	font_p = font_path;
	font_s = font_size;
	loadFont(msg_text, color);
	SDL_QueryTexture(text_texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
}

DynamicText::~DynamicText() {
	//SDL_DestroyTexture(text_texture);
	
}

void DynamicText::Render(int x, int y) {
	rectangle.x = x;
	rectangle.y = y;
	SDL_RenderCopy(GameLoop::renderer, text_texture, nullptr, &rectangle);
}

void DynamicText::loadFont(const char* msg_text, const SDL_Color & color)
{
	font = TTF_OpenFont(font_p.c_str(), font_s);
	SDL_DestroyTexture(text_texture);
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, msg_text, color);
	text_texture = SDL_CreateTextureFromSurface(GameLoop::renderer, text_surface);
	TTF_CloseFont(font);
	SDL_FreeSurface(text_surface);
	return;
}