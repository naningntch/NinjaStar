#pragma once
#include <iostream>
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <string.h>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
using namespace std;
using namespace sf;

class Score
{
private:
	FILE* fp;
	char temp[255];
	unsigned int score[6];
	string name[6];
	vector<pair<int, string>> userScore;
	unsigned int getScore;
	string getName;
	RenderWindow* window;
	Font font;
	Texture backgroundTexture;
	Sprite background;
	Texture homeTexture;
	Sprite homeButton;
	Texture mouseTexture;
	Sprite mouseSprite;
	bool menuState = false;
	Text nameBoard[5];
	Text scoreboard[5];
	Text num[5];

public:
	Score(RenderWindow* window);
	virtual ~Score();
	int highRead();
	void readFile();
	void writeFile(string name, unsigned int score);
	void update();
	void draw();
	void list();
	inline bool	getCheckState() { return this->menuState; }
	inline void	resetState() { this->menuState = false; }

};