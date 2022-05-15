#pragma once
#include <iostream>
#include "GameLoop.h"
#include "TextureLoader.h"
#include "GameObject.h"
#include "Player.h"
#include "Background.h"
#include "GameObject.h"
#include "Text.h"
#include "Player.h"
#include "Selector.h"

enum class MenuSelect{start, options, quit};
enum class ClassSelect{warrior, mage, archer, thief};
class Menu;
class Selector;

class Menu
{
public:
	Menu(int fontsize, const char *font_path, const SDL_Color &color, int x, int y);
	~Menu();

	bool selectingClass = false;

	void Update();
	void Render();

	int getX() { return xpos; }
	int getY() { return ypos; }
	int getSize() { return font_size; }

protected:

	MenuSelect menuState = MenuSelect::start;
	ClassSelect classState = ClassSelect::warrior;
	int xpos = 200;
	int ypos = 50;
	int font_size = 20;

	Text *title, *start, *options, *quit;
public:
	Selector *sel;
};





