#include "Menu.h"
#include "TextureLoader.h"
#include "Selector.h"


Menu::Menu(int fontsize, const char *font_path, const SDL_Color &color, int x = 100, int y = 50) :
	xpos(x), ypos(y), font_size(fontsize)
{
	title = new Text(font_path, fontsize+12, "PUT DUNGEON V 01 BARELY WORKING EDITION", color);
	start = new Text(font_path, fontsize, "START GAME", { 255, 255, 255, 255 });
	options = new Text(font_path, fontsize, "OPTIONS", { 255, 255, 255, 255 });
	quit = new Text(font_path, fontsize, "QUIT", { 255, 255, 255, 255 });
	sel= new Selector("assets/selector.png", 0, 0, 10, 10);
}

Menu::~Menu() {
	delete title, start, options, quit, sel;
}

void Menu::Update()
{
	switch (menuState) {
	case MenuSelect::start: {
		sel->setCoordinates(xpos, 50 + ypos + (1 * font_size));
		break;
	}
	case MenuSelect::options: {
		sel->setCoordinates(xpos, 50 + ypos + (2 * font_size));
		break;
	}
	case MenuSelect::quit: {
		sel->setCoordinates(xpos, 50 + ypos + (3 * font_size));
		break;
	}
	}
	sel->Update();
}

void Menu::Render()
{
	title->Render(xpos, ypos);
	start->Render(xpos + (1 * font_size), 50+ypos+(1*font_size));
	options->Render(xpos + (1 * font_size), 50+ypos + (2 * font_size));
	quit->Render(xpos + (1 * font_size), 50+ypos + (3 * font_size));
	sel->Render();
}


