#include "Player.h"


void Player::Update() {
	xpos++;
	ypos++;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}