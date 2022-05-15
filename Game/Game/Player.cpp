#include "Player.h"


void Player::Update() {

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void Player::MoveUp() {
	ypos -= 32;
}
void Player::MoveDown() {
	ypos += 32;
}
void Player::MoveLeft() {
	xpos -= 32;
}
void Player::MoveRight() {
	xpos += 32;
}