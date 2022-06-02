#include "Player.h"


int Player::playerClass = 0;

Player::Player(const char* texturesheet, int x, int y, int h, int w, int xStart = 1, int yStart = 1, const char* StatsPath = "stats/characters/warrior.txt", int pC = 0) :
	GameObject(texturesheet, x, y, h, w), tileX(xStart), tileY(yStart)
{
	playerClass = pC;
	
	std::ifstream stats;
	stats.open(StatsPath);
	std::string temp;
	float x1;
	stats >> temp >> playerName;
	while (!stats.eof()) {	
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
	NAME = new DynamicText("fonts/arcadeclassic.ttf", 32, (playerName).c_str(), { 255, 255, 255, 255 });
	EQ = new DynamicText("fonts/arcadeclassic.ttf", 32, "EQUIPPED", { 255, 255, 255, 255 });

	MakeStatsText();
}


void Player::RegenFull()
{
	CurrentHealth = PlayerStats["health"];
	CurrentStamina = PlayerStats["stamina"];
	CurrentAmmo = PlayerStats["amunition"];
}

bool Player::Equip(Item &item)
{
	double previousHP = CurrentHealth / PlayerStats["health"];
	if (EquippedItems.find(item.ItemStats["item"]) == EquippedItems.end()) {
		//no item present
		for (auto &it : item.ItemStats) {
			if (it.first == "type") {
				ElementalType[it.second]++;
			}
			else if (it.first != "item") {
				PlayerStats[it.first] += it.second;
			}
		}
		EquippedItems.emplace(item.ItemStats["item"], item);
		CurrentHealth = round(previousHP * PlayerStats["health"]);
		return true;
	}
	else {
		//item present
		for (auto &it : EquippedItems[item.ItemStats["item"]].ItemStats) {
			if (it.first == "type") {
				ElementalType[it.second]--;
			}
			else if (it.first != "item") {
				if (it.first == "health") {
					previousHP = CurrentHealth / PlayerStats["health"];
				}
				PlayerStats[it.first] -= it.second;
			}
		}
		for (auto &it : item.ItemStats) {
			if (it.first == "type") {
				ElementalType[it.second]++;
			}
			else if (it.first != "item") {
				PlayerStats[it.first] += it.second;
			}
		}
		//swaps items
		Item temp = EquippedItems[item.ItemStats["item"]];
		EquippedItems[item.ItemStats["item"]] = item;
		item = temp;
		CurrentHealth = round(previousHP * PlayerStats["health"]);
		return false;
	}
}

void Player::Update() {
	HP->loadLabel(("HP " + std::to_string(CurrentHealth) + "  " + std::to_string((int)PlayerStats["health"])).c_str(), { 255, 255, 255, 255 });
	ST->loadLabel(("ST " + std::to_string(CurrentStamina) + "  " + std::to_string((int)PlayerStats["stamina"])).c_str(), { 255, 255, 255, 255 });
	AMMO->loadLabel(("AMMO " + std::to_string(CurrentAmmo) + "  " + std::to_string((int)PlayerStats["amunition"])).c_str(), { 255, 255, 255, 255 });
	destRect.x = TileMap::getTilePosX(tileX);
	destRect.y = TileMap::getTilePosY(tileY);
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void Player::UpdateStatsText()
{
	int n = 0;
	for (auto ps : PlayerStats) {
		StatsText[n]->loadLabel((ps.first + " " + std::to_string((int)ps.second)).c_str(), { 255, 255, 255, 255 });
		n++;
	}
}

void Player::MakeStatsText()
{
	StatsText.clear();
	for (auto ps : PlayerStats) {
		StatsText.push_back(std::shared_ptr<DynamicText>(new DynamicText("fonts/arcadeclassic.ttf", 20, (ps.first + " " + std::to_string((int)ps.second)).c_str(), { 255, 255, 255, 255 })));
	}
}

Player::~Player()
{
	delete HP, ST, AMMO, NAME, EQ;
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

void Player::RegenRound()
{
	CurrentStamina += PlayerStats["regenr"];
	if (CurrentStamina > PlayerStats["stamina"]) {
		CurrentStamina = PlayerStats["stamina"];
	}
}

void Player::RegenFight()
{
	CurrentHealth += PlayerStats["health"]/10;
	if (CurrentHealth > PlayerStats["health"]) {
		CurrentHealth = PlayerStats["health"];
	}

	CurrentStamina += PlayerStats["regenf"];
	if (CurrentStamina> PlayerStats["stamina"]) {
		CurrentStamina = PlayerStats["stamina"];
	}
	
}

void Player::RenderMinStats(int x, int y) {

	int spacing = 20;
	NAME->Render(x, y);
	HP->Render(x, y+(spacing*1));
	ST->Render(x, y + (spacing * 2));
	AMMO->Render(x, y + (spacing * 3));
}

void Player::Render(int x, int y, bool renderMinStats) {
	if(renderMinStats){
		RenderMinStats(x, y);
	}
	GameObject::Render();
}

void Player::RenderInventory(int xp, int yp)
{
	int spacing = 80;
	int n = 1;
	EQ->Render(xp, yp);
	for (auto &it : EquippedItems) {
		it.second.RenderText(xp, yp+(spacing*n));
		n++;
	}
}

void Player::RenderStats(int xp, int yp)
{
	int spacing = 20;
	int n = 1;
	NAME->Render(xp, yp);
	for (auto &st : StatsText) {
		st->Render(xp, yp + 20 + (spacing*n));
		n++;
	}
}

///////////////////////////
//
//ITEMS//
//
//////////////////////////

Item::Item(SDL_Texture *& text, int x = 1, int y = 1):
	GameObject(text, 0, 0, 32, 32)
{
	xPos = x;
	yPos = y;
	int ItemRarity = rand() % (100 + (GameLoop::floorLevel + GameLoop::floorLevel * 7));
	std::ifstream fileStats;
	std::string filePath = "stats/items/";
	if (ItemRarity < 70) { //common
		filePath += "common/";
		int tempRand = rand() % 4;
		switch (tempRand) {
		case 0: {
			filePath += "amulet";
			break;
		}
		case 1: {
			filePath += "boots";
			break;
		}
		case 2: {
			filePath += "chest";
			break;
		}
		case 3: {
			filePath += "ring";
			break;
		}
		}
		tempRand = rand() % 4;
		switch (tempRand) {
		case 0: {
			filePath += "erth";
			break;
		}
		case 1: {
			filePath += "fire";
			break;
		}
		case 2: {
			filePath += "wate";
			break;
		}
		case 3: {
			filePath += "wind";
			break;
		}
		}
	}
	else {
		if (ItemRarity < 80) { //green
			filePath += "green/";
		}
		else if (ItemRarity < 90) { //blue
			filePath += "blue/";
		}
		else if (ItemRarity < 100) { //red
			filePath += "red/";
		}
		else if (ItemRarity < 110) { //black
			filePath += "black/";
		}
		else { //rainbow
			filePath += "rainbow/";
		}
		switch (Player::playerClass) {
		case 0: {
			bool sworsh = rand() % 2;
			if (sworsh) {
				filePath += "sword";
			}
			else {
				filePath += "shield";
			}
			break;
		}
		case 1: {
			filePath += "staff";
			break;
		}
		case 2: {
			filePath += "bow";
			break;
		}
		case 3: {
			filePath += "daggers";
			break;
		}
		}

	}
	filePath += ".txt";
	fileStats.open(filePath);

	float tempStats;
	std::string tempKey;
	fileStats >> tempKey >> itemName;
	name = new DynamicText("fonts/arcadeclassic.ttf", 20, (itemName).c_str(), { 255, 255, 255, 255 });
	while (!fileStats.eof()) {
		fileStats >> tempKey;
		fileStats >> tempStats;
		ItemStats.try_emplace(tempKey, tempStats);
	}
	fileStats.close();
	GenerateText();
}

Item::Item(int x = 1, int y = 1) :
	GameObject("assets/item.png", 0, 0, 32, 32)
{
	xPos = x;
	yPos = y;
	int ItemRarity = rand() % (100 + (GameLoop::floorLevel + GameLoop::floorLevel * 7));
	std::ifstream fileStats;
	std::string filePath = "stats/items/";
	if (ItemRarity < 70) { //common
		filePath += "common/";
		int tempRand = rand() % 4;
		switch (tempRand) {
		case 0: {
			filePath += "amulet";
			break;
		}
		case 1: {
			filePath += "boots";
			break;
		}
		case 2: {
			filePath += "chest";
			break;
		}
		case 3: {
			filePath += "ring";
			break;
		}
		}
		tempRand = rand() % 4;
		switch (tempRand) {
		case 0: {
			filePath += "erth";
			break;
		}
		case 1: {
			filePath += "fire";
			break;
		}
		case 2: {
			filePath += "wate";
			break;
		}
		case 3: {
			filePath += "wind";
			break;
		}
		}
	}
	else {
		if (ItemRarity < 80) { //green
			filePath += "green/";
		}
		else if (ItemRarity < 90) { //blue
			filePath += "blue/";
		}
		else if (ItemRarity < 100) { //red
			filePath += "red/";
		}
		else if (ItemRarity < 110) { //black
			filePath += "black/";
		}
		else { //rainbow
			filePath += "rainbow/";
		}
		switch (Player::playerClass) {
		case 0: {
			bool sworsh = rand() % 2;
			if (sworsh) {
				filePath += "sword";
			}
			else {
				filePath += "shield";
			}
			break;
		}
		case 1: {
			filePath += "staff";
			break;
		}
		case 2: {
			filePath += "bow";
			break;
		}
		case 3: {
			filePath += "daggers";
			break;
		}
		}

	}
	filePath += ".txt";
	fileStats.open(filePath);

	float tempStats;
	std::string tempKey;
	fileStats >> tempKey >> itemName;
	name = new DynamicText("fonts/arcadeclassic.ttf", 20, (itemName).c_str(), { 255, 255, 255, 255 });
	while (!fileStats.eof()) {
		fileStats >> tempKey;
		fileStats >> tempStats;
		ItemStats.try_emplace(tempKey, tempStats);
	}
	fileStats.close();
	GenerateText();
}

Item::~Item()
{
}

void Item::Render()
{
	if (onGround) {
		GameObject::Render();
	}
}

void Item::UpdateText()
{
	name->loadLabel((itemName).c_str(), { 255, 255, 255, 255 });
	auto statsIt = ItemStats.begin();
	for (auto it : ItemText) {
		std::string temp = statsIt->first + " " + std::to_string(statsIt->second);
		it->loadLabel(temp.c_str(), { 255, 255, 255, 255 });
		statsIt++;
	}
}

void Item::GenerateText()
{
	for (auto &x : ItemStats)
	{
		if (x.first == "type" or x.first == "item") {

		}
		else {
			std::string temp = x.first + " " + std::to_string(x.second);
			ItemText.push_back(std::shared_ptr<DynamicText> (new DynamicText("fonts/arcadeclassic.ttf", 20, temp.c_str(), { 255, 255, 255, 255 })));
		}
	}
}

void Item::RenderText(int xp, int yp)
{

	int spacing = 16, n = 0;
	name->Render(xp, yp + (spacing*n));
	n++;
	for (auto &x : ItemText)
	{
		x->Render(xp, yp + (spacing*n));
		n++;
	}
}



void Item::Update()
{
	destRect.x = TileMap::getTilePosX(xPos);
	destRect.y = TileMap::getTilePosY(yPos);
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}
