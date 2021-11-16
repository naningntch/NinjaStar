#include "Menu.h"

Menu::Menu(RenderWindow* window)
{
	this->window = window;
	for (size_t i = 0; i < 3; i++)
	{
		this->menuTexture[i].loadFromFile("Texture/menu/main/" + to_string(i) + ".png");
		this->menu[i].setTexture(this->menuTexture[i]);
		if (i >= 1)
		{
			this->menu[i].setOrigin(menuTexture[i].getSize().x / 2, menuTexture[i].getSize().y / 2);
		}
	}
	this->inputTexture.loadFromFile("Texture/menu/main/input.jpg");
	this->input.setTexture(this->inputTexture);

	this->homeTexture.loadFromFile("Texture/menu/5.png");
	this->homeButton.setTexture(this->homeTexture);
	this->homeButton.setOrigin(homeTexture.getSize().x / 2, homeTexture.getSize().y / 2);
	this->homeButton.setPosition(1310, 60);

	this->playButton.setTexture(this->menuTexture[1]);
	this->playButton.setOrigin(menuTexture[1].getSize().x / 2, menuTexture[1].getSize().y / 2);
	this->playButton.setPosition(445 + menuTexture[1].getSize().x / 2, 487 + menuTexture[1].getSize().y / 2);



	this->menu[1].setPosition(692.5, 452.5);
	this->menu[2].setPosition(692.5, 632.5);
	this->mouseTexture.loadFromFile("Texture/menu/mouse.png");
	this->mouseSprite.setTexture(this->mouseTexture);
	this->mouseSprite.setScale(0.12f, 0.12f);
	this->mouseSprite.setOrigin(Vector2f(this->mouseTexture.getSize().x / 2, this->mouseTexture.getSize().y / 2));

	this->buttonBuffer.loadFromFile("Sound/button_sfx.wav");
	this->buttonSfx.setBuffer(buttonBuffer);
	this->font.loadFromFile("Font/font.ttf");

	this->playerText.setString("Enter  Your  Name");
	this->playerText.setFont(this->font);
	this->playerText.setCharacterSize(80);
	this->playerText.setFillColor(Color::Black);
	this->playerText.setPosition(683, 330);
	this->playerText.setLetterSpacing(1.5);
	this->playerText.setOutlineThickness(3);
	this->playerText.setOutlineColor(Color::White);
	this->playerText.setOrigin(this->playerText.getLocalBounds().width / 2, this->playerText.getLocalBounds().height / 2);

}

void Menu::update()
{
	this->mouseSprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(*this->window)));
	for (size_t i = 1; i < 3; i++)
	{
		if (menu[i].getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
		{

			this->menu[i].setScale(1.1f, 1.1f);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				buttonSfx.play();
				switch (i)
				{
				case 1:
					if (state == MENU)
						updateMenuState(INPUT);
					break;
				case 2:
					if (state == MENU)
						updateMenuState(SCORE);
					break;
				default:
					break;
				}
			}
		}
		else
		{
			this->menu[i].setScale(1.f, 1.f);
		}
	}
}

void Menu::draw()
{
	this->window->clear();
	for (size_t i = 0; i < 3; i++)
	{
		this->window->draw(menu[i]);
	}
	this->window->draw(this->mouseSprite);
	this->window->display();

}

void Menu::updateMenuState(int action)
{
	switch (action)
	{
	case 0:
		this->state = MENU;
		break;
	case 1:
		this->state = INPUT;
		break;
	case 2:
		this->state = PLAY;
		break;
	case 3:
		this->state = SCORE;
		break;

	default:
		break;
	}
}

void Menu::updateInput(vector<Event> events)
{
	this->mouseSprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(*this->window)));
	if (homeButton.getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
	{
		this->homeButton.setScale(0.23f, 0.23f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			updateMenuState(MENU);
		}
	}
	else
	{
		this->homeButton.setScale(0.2f, 0.2f);
	}

	if (playButton.getGlobalBounds().contains(Vector2f(Mouse::getPosition())) && playerName.length() > 0)
	{
		this->playButton.setScale(1.1f, 1.1f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			updateMenuState(PLAY);
		}
	}
	else
	{
		this->playButton.setScale(1.f, 1.f);
	}
	for (size_t i = 0; i < events.size(); i++)
	{
		if (events[i].text.unicode != 32 && !Keyboard::isKeyPressed(Keyboard::Enter) && events[i].text.unicode != 63)
		{
			if (events[i].text.unicode == 8 && playerName.length() > 0)
			{
				playerName.erase(playerName.length() - 1);
			}
			else if (events[i].text.unicode < 128 && playerName.length() < 15 && events[i].text.unicode != 8)
			{
				playerName += static_cast<char>(events[i].text.unicode);
			}
			playerText.setString(playerName);
			this->playerText.setOrigin(this->playerText.getLocalBounds().width / 2, this->playerText.getLocalBounds().height / 2);
		}
	}
}

void Menu::inputMenu()
{

	this->window->clear();
	this->window->draw(input);
	this->window->draw(homeButton);
	this->window->draw(playButton);
	this->window->draw(playerText);
	this->window->draw(this->mouseSprite);
	this->window->display();
}


