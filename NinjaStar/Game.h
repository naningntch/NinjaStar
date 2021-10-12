#pragma once
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include <vector>

class Game
{
private:
	RenderWindow *window;
	vector<Player> player;
	vector<Enemy> enemies;
	vector<Background> backgrounds;
	Texture playerTexture;
	Texture backgroundTexture[3];
	Texture bulletTexture;
	Texture enemyTexture;
	float spawnTimerMax;
	float spawnTimer;

public:
	Game(RenderWindow *window);
	void Update(float deltaTime);
	void Draw();
};

