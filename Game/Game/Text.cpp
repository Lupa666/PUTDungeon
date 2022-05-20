#include "Text.h"
#include <iostream>
#include "GameLoop.h"

Text::Text(const char* font_path, int font_size, const char* msg_text, const SDL_Color &color) {
	text_texture = loadFont(font_path, font_size, msg_text, color);
	SDL_QueryTexture(text_texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
}

void Text::Render(int x, int y){
	rectangle.x = x;
	rectangle.y = y;
	SDL_RenderCopy(GameLoop::renderer, text_texture, nullptr, &rectangle);
}

SDL_Texture * Text::loadFont(const char* font_path, int font_size, const char* msg_text, const SDL_Color & color)
{
	TTF_Font *font = TTF_OpenFont(font_path, font_size);
	auto text_surface = TTF_RenderText_Solid(font, msg_text, color);
	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(GameLoop::renderer, text_surface);
	SDL_FreeSurface(text_surface);
	return text_texture;
}