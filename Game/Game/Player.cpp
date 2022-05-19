#include "Player.h"


void Player::Update() {

	destRect.x = TileMap::getTilePosX(tileX);
	destRect.y = TileMap::getTilePosY(tileY);
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
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
