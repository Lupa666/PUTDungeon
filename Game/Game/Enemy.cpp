#include "Enemy.h"
#include "GameLoop.h"
#include "TileMap.h"
#include "TextureLoader.h"


Enemy::Enemy(const char* texture = "assets/enemy.png", int xpos = 4, int ypos = 4):
	GameObject(texture, 0, 0, 32, 32)
{
	tileX = xpos;
	tileY = ypos;
	srcRect.x = 0;
	srcRect.y = 0;
}

Enemy::Enemy(SDL_Texture *& text, int xpos = 4, int ypos = 4) :
	GameObject(text, 0, 0, 32, 32)
{
	tileX = xpos;
	tileY = ypos;
	srcRect.x = 0;
	srcRect.y = 0;
}

Enemy::~Enemy()
{
	//delete NAME, HP, STAMINA;
}

void Enemy::LoadStats()
{
}

void Enemy::SetText(int, int)
{
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

void Enemy::Render()
{
	SDL_RenderCopy(GameLoop::renderer, objTexture, &srcRect, &destRect);
}

void Enemy::RenderText(int, int)
{
}
