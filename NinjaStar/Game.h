#pragma once
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Item.h"
#include "Score.h"
#include "Menu.h"
#include <vector>
#include <string>


class Game
{
private:
	RenderWindow* window;
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
	Text coinText;
	Texture coinIcon;
	Texture scoreIcon;
	Text scoreText;
	Font font;
	Sprite coin;
	Sprite score;
	size_t scores;
	size_t coins;
	size_t scoreMultiplier;

	//soundsfx
	SoundBuffer boomBuffer;
	Sound boomSfx;
	SoundBuffer shurikenBuffer;
	Sound shurikenSfx;
	SoundBuffer coinBuffer;
	Sound coinSfx;
	SoundBuffer healBuffer;
	Sound healSfx;
	SoundBuffer invisibleBuffer;
	Sound invisibleSfx;
	SoundBuffer getdmgBuffer;
	Sound getdmgSfx;
	SoundBuffer buttonBuffer;
	Sound buttonSfx;
	


	float multiplierTimerMax;
	float multiplierTimer;
	int multiplierAdderMax;
	int multiplierAdder;

	float spawnTimerMax;
	float spawnTimer;
	bool playerAlive = true;
	RectangleShape hpBar[2];
	CircleShape logo;

	float healCooldown;
	bool useHeal;
	bool usingHeal;

	float invisCooldown;
	bool useInvis;
	bool usingInvis;

	Texture skillTexture[2];
	Sprite skill[2];
	Text heal;
	Text invisible;
	Texture menuTexture;
	Texture buttonTexture[5];
	Sprite menu;
	Sprite button[5];

	Texture gameOverTexture;
	RectangleShape gameOver;

	Text scoreOver;
	Text highScore;

	Texture popupWindowTexture;
	Sprite popupWindow;

	bool popupState = false;
	bool scoreAdd = false;
	bool menuState = false;

	string playerName;

public:
	Game(RenderWindow* window);
	inline void setPlayerName(string playerName) { this->playerName = playerName; }
	inline bool	getCheckState() { return this->menuState; }
	inline void	resetState() { this->menuState = false; }
	void initUI();
	void initAudio();
	void UpdatePlayerUI(int index);
	void Update(float deltaTime);
	void Draw();
	void GameOver();
	void GameReset();

};

