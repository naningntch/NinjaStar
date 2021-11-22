#define _CRT_SECURE_NO_WARNINGS
#include "Score.h"

Score::Score(RenderWindow* window)
{
	this->window = window;
	this->backgroundTexture.loadFromFile("Texture/menu/main/score.jpg");
	this->background.setTexture(this->backgroundTexture);

	this->homeTexture.loadFromFile("Texture/menu/5.png");
	this->homeButton.setTexture(this->homeTexture);
	this->homeButton.setOrigin(homeTexture.getSize().x / 2, homeTexture.getSize().y / 2);
	this->homeButton.setPosition(1310, 60);
	this->mouseTexture.loadFromFile("Texture/menu/mouse.png");
	this->mouseSprite.setTexture(this->mouseTexture);
	this->mouseSprite.setScale(0.12f, 0.12f);
	this->mouseSprite.setOrigin(Vector2f(this->mouseTexture.getSize().x / 2, this->mouseTexture.getSize().y / 2));
	this->font.loadFromFile("Font/font.ttf");
	this->buttonBuffer.loadFromFile("Sound/button_sfx.wav");
	this->buttonSfx.setBuffer(buttonBuffer);
}

Score::~Score()
{

}

int Score::highRead()
{
	readFile();
	sort(this->userScore.begin(), this->userScore.end());
	fclose(this->fp);
	return userScore[userScore.size() - 1].first;
}

void Score::readFile()
{
	this->fp = fopen("./System/score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		this->userScore.push_back(make_pair(this->score[i], this->name[i]));
	}
}

void Score::writeFile(string name, unsigned int score)
{
	readFile();
	this->name[5] = name;
	this->score[5] = score;
	this->userScore.push_back(make_pair(this->score[5], this->name[5]));
	sort(this->userScore.begin(), this->userScore.end());
	fclose(this->fp);

	fopen("./System/score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}
	fclose(this->fp);

}

void Score::update()
{
	this->mouseSprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(*this->window)));
	if (homeButton.getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
	{
		this->homeButton.setScale(0.23f, 0.23f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			buttonSfx.play();
			menuState = true;
		}
	}
	else
	{
		this->homeButton.setScale(0.2f, 0.2f);
	}
}

void Score::draw()
{
	this->window->clear();
	this->window->draw(background);
	this->window->draw(homeButton);
	list();
	this->window->draw(mouseSprite);
	this->window->display();
}

void Score::list()
{
	readFile();
	fclose(this->fp);
	for (size_t i = 0; i < 5; i++)
	{
		this->num[i].setFont(this->font);
		this->nameBoard[i].setFont(this->font);
		this->scoreboard[i].setFont(this->font);

		this->num[i].setCharacterSize(50);
		this->nameBoard[i].setCharacterSize(50);
		this->scoreboard[i].setCharacterSize(50);

		this->num[i].setFillColor(Color::Black);
		this->nameBoard[i].setFillColor(Color::Black);
		this->scoreboard[i].setFillColor(Color::Black);

		this->num[i].setPosition(400.f, 300.f + (i * 90));
		this->nameBoard[i].setPosition(450.f, 300.f + (i * 90));
		this->scoreboard[i].setPosition(1000.f, 300.f + (i * 90));

		this->num[i].setOrigin(0, this->num[i].getLocalBounds().height);
		this->nameBoard[i].setOrigin(0, this->nameBoard[i].getLocalBounds().height);
		this->scoreboard[i].setOrigin(scoreboard[i].getLocalBounds().width, this->scoreboard[i].getLocalBounds().height);

		this->num[i].setString(to_string(i + 1) + ". ");
		this->nameBoard[i].setString(name[i]);
		this->scoreboard[i].setString(to_string(score[i]));

		this->window->draw(this->num[i]);
		this->window->draw(this->nameBoard[i]);
		this->window->draw(this->scoreboard[i]);




	}
}
