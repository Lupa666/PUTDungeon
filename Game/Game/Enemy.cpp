#include "Enemy.h"
#include "GameLoop.h"
#include "TileMap.h"
#include "TextureLoader.h"


Enemy::Enemy(const char* texture = "assets/enemy.png", int xpos = 4, int ypos = 4):
	GameObject(texture, 0, 0, 32, 32),
	NAME("fonts/arcadeclassic.ttf", 28, "TEMP", { 255, 255, 255, 255 }),
	HP("fonts/arcadeclassic.ttf", 28, "TEMP", { 255, 255, 255, 255 }),
	STAMINA("fonts/arcadeclassic.ttf", 28, "TEMP", { 255, 255, 255, 255 })
{
	tileX = xpos;
	tileY = ypos;
	srcRect.x = 0;
	srcRect.y = 0;
	LoadStats();
	NAME.loadFont(enemyName.c_str(), { 255, 255, 255, 255 });
	UpdateText();
}

Enemy::Enemy(SDL_Texture *& text, int xpos = 4, int ypos = 4) :
	GameObject(text, 0, 0, 32, 32),
	NAME("fonts/arcadeclassic.ttf", 28, "TEMP", { 255, 255, 255, 255 }),
	HP("fonts/arcadeclassic.ttf", 28, "TEMP", { 255, 255, 255, 255 }),
	STAMINA("fonts/arcadeclassic.ttf", 28, "TEMP", { 255, 255, 255, 255 })
{
	tileX = xpos;
	tileY = ypos;
	LoadStats();
	NAME.loadFont(enemyName.c_str(), { 255, 255, 255, 255 });
	UpdateText();
}

Enemy::~Enemy()
{
}

void Enemy::LoadStats()
{
	std::string filepath;
	filepath += "stats/enemies/";
	int monst = rand() % 16;
	switch (monst) {
	case 0: { filepath += "cerber.txt"; break; }
	case 1: { filepath += "elementalfire.txt"; break; }
	case 2: { filepath += "elementalerth.txt"; break; }
	case 3: { filepath += "elementalwate.txt"; break; }
	case 4: { filepath += "elementalwind.txt"; break; }
	case 5: { filepath += "golemfire.txt"; break; }
	case 6: { filepath += "golemerth.txt"; break; }
	case 7: { filepath += "golemwate.txt"; break; }
	case 8: { filepath += "golemwind.txt"; break; }
	case 9: { filepath += "gryf.txt"; break; }
	case 10: { filepath += "koliber.txt"; break; }
	case 11: { filepath += "minotaur.txt"; break; }
	case 12: { filepath += "nietoperz.txt"; break; }
	case 13: { filepath += "ropucha.txt"; break; }
	case 14: { filepath += "troll.txt"; break; }
	case 15: { filepath += "wampir.txt"; break; }
	default: {std::cout << "WRONG FILE READ"; break; }
	}
	
	std::ifstream fileStats;
	fileStats.open(filepath);

	fileStats >> srcRect.x >> srcRect.y;
	while (!fileStats.eof()) {
		std::string key;
		fileStats >> key;
		if (key == "name") {
			fileStats >> enemyName;
		}
		else {
			float value;
			fileStats >> value;
			EnemyStats.try_emplace(key, value);
		}
	}
	currentHP = EnemyStats["health"];
	currentStamina = EnemyStats["stamina"];
	
	fileStats.close();
}

void Enemy::LoadTexture(const char * filepath = "assets/enemy.png")
{
	objTexture = TextureLoader::LoadText(filepath);
}



void Enemy::Update()
{
	destRect.x = TileMap::getTilePosX(tileX);
	destRect.y = TileMap::getTilePosY(tileY);
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void Enemy::UpdateText()
{
	HP.loadFont(("HP " + std::to_string((int)currentHP) + " " + std::to_string((int)EnemyStats["health"])).c_str(), { 255, 255, 255, 255 });
	STAMINA.loadFont(("ST " + std::to_string((int)currentStamina) + " " + std::to_string((int)EnemyStats["stamina"])).c_str(), { 255, 255, 255, 255 });
}

void Enemy::Render()
{
	SDL_RenderCopy(GameLoop::renderer, objTexture, &srcRect, &destRect);
}

void Enemy::RenderText(int xpos, int ypos)
{
	int n = 0;
	int spacing = 20;
	NAME.Render(xpos, ypos + (n*spacing));
	n++;
	HP.Render(xpos, ypos + (n*spacing));
	n++;
	STAMINA.Render(xpos, ypos + (n*spacing));
}
