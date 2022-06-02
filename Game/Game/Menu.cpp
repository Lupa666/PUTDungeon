#include "Menu.h"
#include "TextureLoader.h"
#include "Selector.h"


Menu::Menu(int fontsize, const char *font_path, const SDL_Color &color, int x = 100, int y = 50) :
	xpos(x), ypos(y), font_size(fontsize)
{
	title = new Text(font_path, fontsize+12, "PUT DUNGEON", color);
	start = new Text(font_path, fontsize, "START GAME", { 255, 255, 255, 255 });
	options = new Text(font_path, fontsize, "AUTHORS", { 255, 255, 255, 255 });
	quit = new Text(font_path, fontsize, "QUIT", { 255, 255, 255, 255 });

	warrior = new Text(font_path, fontsize, "WARRIOR", { 255, 255, 255, 255 });
	mage = new Text(font_path, fontsize, "MAGE", { 255, 255, 255, 255 });
	archer = new Text(font_path, fontsize, "ARCHER", { 255, 255, 255, 255 });
	thief = new Text(font_path, fontsize, "ROGUE", { 255, 255, 255, 255 });

	authors = new Text(font_path, fontsize, "BARTOSZ SOJKA I WIKTOR PAWLAK", { 255, 255, 255, 255 });

	sel= new Selector("assets/selector.png", 0, 0, 10, 10);
}

Menu::~Menu() {
	delete title, start, options, quit, sel, warrior, mage, archer, thief, authors;
}

void Menu::Update()
{	
	if (startSelect) {
		switch (classState) {
		case ClassSelect::warrior: {
			sel->setCoordinates(200 + xpos + (1 * font_size), 50 + ypos + (1 * font_size));
			break;
		}
		case ClassSelect::mage: {
			sel->setCoordinates(200 + xpos + (1 * font_size), 50 + ypos + (2 * font_size));
			break;
		}
		case ClassSelect::archer: {
			sel->setCoordinates(200 + xpos + (1 * font_size), 50 + ypos + (3 * font_size));
			break;
		}
		case ClassSelect::thief: {
			sel->setCoordinates(200 + xpos + (1 * font_size), 50 + ypos + (4 * font_size));
			break;
		}
		}
	}else switch (menuState) {
	case MenuSelect::start: {
		sel->setCoordinates(xpos, 50 + ypos + (1 * font_size));
		break;
	}
	case MenuSelect::authors: {
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
	if (startSelect) {
		warrior->Render(238 + xpos + (1 * font_size), 50 + ypos + (1 * font_size));
		mage->Render(238 + xpos + (1 * font_size), 50 + ypos + (2 * font_size));
		archer->Render(238 + xpos + (1 * font_size), 50 + ypos + (3 * font_size));
		thief->Render(238 + xpos + (1 * font_size), 50 + ypos + (4 * font_size));
	}
	if (authorsDisplay) {
		authors->Render(238 + xpos + (1 * font_size), 50 + ypos + (1 * font_size));
	}
	title->Render(xpos, ypos);
	start->Render(xpos + (1 * font_size), 50+ypos+(1*font_size));
	options->Render(xpos + (1 * font_size), 50+ypos + (2 * font_size));
	quit->Render(xpos + (1 * font_size), 50+ypos + (3 * font_size));
	sel->Render();
}

void Menu::ResetState() {
	startSelect = false;
	authorsDisplay = false;
	classState = ClassSelect::warrior;
}

void Menu::MoveUp()
{
	if (authorsDisplay) {
		authorsDisplay = false;
	}
	if (startSelect) {
		switch (classState) {
		case ClassSelect::warrior: {
			classState = ClassSelect::thief;
			break;
		}
		case ClassSelect::mage: {
			classState = ClassSelect::warrior;
			break;
		}
		case ClassSelect::archer: {
			classState = ClassSelect::mage;
			break;
		}
		case ClassSelect::thief: {
			classState = ClassSelect::archer;
			break;
		}
		}
	}else switch (menuState) {
	case MenuSelect::start: {
		menuState = MenuSelect::quit;
		break;
	}
	case MenuSelect::authors: {
		menuState = MenuSelect::start;
		break;
	}
	case MenuSelect::quit: {
		menuState = MenuSelect::authors;
		break;
	}
	}
}

void Menu::MoveDown()
{
	if (authorsDisplay) {
		authorsDisplay = false;
	}
	if (startSelect) {
		switch (classState) {
		case ClassSelect::warrior: {
			classState = ClassSelect::mage;
			break;
		}
		case ClassSelect::mage: {
			classState = ClassSelect::archer;
			break;
		}
		case ClassSelect::archer: {
			classState = ClassSelect::thief;
			break;
		}
		case ClassSelect::thief: {
			classState = ClassSelect::warrior;
			break;
		}
		}
	}
	else switch (menuState) {
	case MenuSelect::start: {
		menuState = MenuSelect::authors;
		break;
	}
	case MenuSelect::authors: {
		menuState = MenuSelect::quit;
		break;
	}
	case MenuSelect::quit: {
		menuState = MenuSelect::start;
		break;
	}
	}
}


