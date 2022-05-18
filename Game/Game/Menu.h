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

enum class MenuSelect{start, authors, quit};
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

	MenuSelect getMenuState() const { return menuState; }
	ClassSelect getClassState() const { return classState; }
	int getX() { return xpos; }
	int getY() { return ypos; }
	int getSize() { return font_size; }
	bool getStartSelect() { return startSelect; }
	bool getAuthorDisplay() { return authorsDisplay; }
	void MoveUp();
	void MoveDown();
	void ResetState();
	void PressStart() { startSelect = !startSelect; }
	void PressAuthors() { authorsDisplay = !authorsDisplay; }


protected:

	bool startSelect = false;
	bool authorsDisplay = false;
	MenuSelect menuState = MenuSelect::start;
	ClassSelect classState = ClassSelect::warrior;
	int xpos = 200;
	int ypos = 50;
	int font_size = 20;

	Text *title, *start, *options, *quit;
	Text *warrior, *mage, *archer, *thief;
	Text *authors;
	Selector *sel;
};





