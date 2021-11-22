#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
using namespace std;
using namespace sf;
class Menu
{
private:
	RenderWindow* window;
	Sprite menu[3];
	Texture menuTexture[3];
	Texture mouseTexture;
	Sprite mouseSprite;
	Sound buttonSfx;
	SoundBuffer buttonBuffer;
	Texture inputTexture;
	Sprite input;
	Sprite playButton;
	Sprite homeButton;
	Texture homeTexture;
	string playerName;
	Text playerText;
	Font font;
	
	

	enum State
	{
		MENU,
		INPUT,
		PLAY,
		SCORE
	};

	State state = State::MENU;

public:
	Menu(RenderWindow* window);
	inline int getState() { return this->state; }
	inline string getPlayerName() { return this->playerName; }
	void update();
	void draw();
	void updateMenuState(int action);
	void inputMenu();
	void updateInput(vector<Event> events);
	inline void setActionToZero() { this->state = MENU; }
	inline void ResetName()
	{
		this->playerName.clear();
		this->playerText.setString("Enter  Your  Name!");
		this->playerText.setOrigin(this->playerText.getLocalBounds().width / 2, this->playerText.getLocalBounds().height / 2);
	};
	

};

