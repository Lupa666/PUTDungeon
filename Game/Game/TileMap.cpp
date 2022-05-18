#include "TileMap.h"
#include <fstream>

TileMap::TileMap(int x, int y)
{
	tiles[0] = new Tile("assets/wall.png", 32, 32);
	tiles[1] = new Tile("assets/ground.png", 32, 32);
	tiles[2] = new Tile("assets/selector.png", 32, 32);
	xStart = x;
	yStart = y;
}

TileMap::~TileMap()
{
	delete tiles[0], tiles[1], tiles[2];
}

void TileMap::Update()
{
}

void TileMap::Render()
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			int xRender, yRender;
			xRender = xStart + j*size;
			yRender = yStart + i*size;
			tiles[MapArea[j][i]]->Render(xRender, yRender);
			}
		}
	}

bool TileMap::checkWallCollision(int x, int y)
{
	return MapArea[x][y];
}

int TileMap::getTilePosX(int x)
{	
	return xStart + x * size;
}

int TileMap::getTilePosY(int y)
{
	return yStart + y * size;
}

void TileMap::LoadMap(const char* filepath = "maps/map1.txt")
{
	std::ifstream mapFile;
	mapFile.open(filepath);
	if (!mapFile.is_open()) {
		std::cout << "Couldn't open map!\n";
	}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			mapFile >> MapArea[j][i];
		}
	}
	mapFile.close();
}

int TileMap::xStart = 0;
int TileMap::yStart = 64;
int TileMap::size = 32;

Tile::Tile(const char* texturesheet, int h, int w)
{
	
	srcRect.h = h;
	srcRect.w = w;
	srcRect.x = 0;
	srcRect.y = 0;
	objTexture = TextureLoader::LoadText(texturesheet);
}

Tile::~Tile()
{
}

void Tile::Render(int x, int y)
{
	destRect.x = x;
	destRect.y = y;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
	SDL_RenderCopy(GameLoop::renderer, objTexture, &srcRect, &destRect);
}
