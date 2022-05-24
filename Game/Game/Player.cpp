#include "Player.h"


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