#pragma once
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Item.h"
#include <vector>

class Game
{
private:
	RenderWindow *window;
	vector<Player> player;
	vector<Enemy> enemies;
	vector<Background> backgrounds;
	vector<Item> items;
	Texture playerTexture;
	Texture backgroundTexture[3];
	Texture bulletTexture;
	Texture enemyTexture;
	Texture itemTexture;
	Texture logoTexture;
	Texture mouseTexture;
	Sprite mouseSprite;

	float spawnTimerMax;
	float spawnTimer;
	bool playerAlive = true;
	RectangleShape hpBar[2];
	CircleShape logo;

public:
	Game(RenderWindow *window);
	void UpdatePlayerUI(int index);
	void Update(float deltaTime);
	void Draw();
};

