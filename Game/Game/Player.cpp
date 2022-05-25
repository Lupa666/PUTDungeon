#include "Player.h"


int Player::playerClass = 0;

Player::Player(const char* texturesheet, int x, int y, int h, int w, int xStart = 1, int yStart = 1, const char* StatsPath = "stats/characters/warrior.txt", int pC = 0) :
	GameObject(texturesheet, x, y, h, w), tileX(xStart), tileY(yStart)
{
	playerClass = pC;
	std::ifstream stats;
	stats.open(StatsPath);
	while (!stats.eof()) {
		std::string temp;
		float x1;
		stats >> temp >> x1;
		PlayerStats.insert_or_assign(temp, x1);
	}
	stats.close();
	CurrentHealth = PlayerStats["health"];
	CurrentStamina = PlayerStats["stamina"];
	CurrentAmmo = PlayerStats["amunition"];

	HP = new DynamicText("fonts/arcadeclassic.ttf", 24, ("HP  " + std::to_string(CurrentHealth) + "  " + std::to_string((int)PlayerStats["health"])).c_str(), { 255, 255, 255, 255 });
	ST = new DynamicText("fonts/arcadeclassic.ttf", 24, ("ST  " + std::to_string(CurrentStamina) + "  " + std::to_string((int)PlayerStats["stamina"])).c_str(), { 255, 255, 255, 255 });
	AMMO = new DynamicText("fonts/arcadeclassic.ttf", 24, ("AMMO" + std::to_string(CurrentAmmo) + "  " + std::to_string((int)PlayerStats["amunition"])).c_str(), { 255, 255, 255, 255 });
}


void Player::Update() {
	HP->loadFont(("HP " + std::to_string(CurrentHealth) + "  " + std::to_string((int)PlayerStats["health"])).c_str(), { 255, 255, 255, 255 });
	ST->loadFont(("ST " + std::to_string(CurrentStamina) + "  " + std::to_string((int)PlayerStats["stamina"])).c_str(), { 255, 255, 255, 255 });
	AMMO->loadFont(("AMMO " + std::to_string(CurrentAmmo) + "  " + std::to_string((int)PlayerStats["amunition"])).c_str(), { 255, 255, 255, 255 });
	destRect.x = TileMap::getTilePosX(tileX);
	destRect.y = TileMap::getTilePosY(tileY);
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

Player::~Player()
{
	delete HP, ST, AMMO;
}

void Player::MoveUp(bool tileCheck) {
	if (tileCheck) {
		tileY--;
	}
}
void Player::MoveDown(bool tileCheck) {
	if (tileCheck) {
		tileY++;
	}
}
void Player::MoveLeft(bool tileCheck) {
	if (tileCheck) {
		tileX--;
	}
}
void Player::MoveRight(bool tileCheck) {
	if (tileCheck) {
		tileX++;
	}
}

void Player::SetPos(int x, int y)
{
	tileX = x;
	tileY = y;
}

void Player::Render() {
	HP->Render(16, 430);
	ST->Render(16, 460);
	AMMO->Render(16, 490);
	GameObject::Render();
}