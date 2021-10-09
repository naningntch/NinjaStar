#pragma once
#include "Player.h"
#include "Background.h"
#include <vector>
class Game
{
private:
	RenderWindow *window;
	vector<Player> player;
	vector<Background> backgrounds;
	Texture playerTexture;
	Texture backgroundTexture[3];
	Texture bulletTexture;
public:
	Game(RenderWindow *window);
	void Update(float deltaTime);
	void Draw();
};

