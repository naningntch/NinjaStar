#include "Game.h"

Game::Game(RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(60);
	this->playerTexture.loadFromFile("Texture/Player/sprite.png");
	this->bulletTexture.loadFromFile("Texture/Player/bullet.png");
	this->player.push_back(Player(&this->playerTexture, &this->bulletTexture, Vector2u(5, 2), 0.065f));
	for (size_t i = 0; i < 3; i++)
	{
		this->backgroundTexture[i].loadFromFile("Texture/Background/" + to_string(i) + ".png");

	}
	this->backgrounds.push_back(Background(&this->backgroundTexture[0], -60.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[1], -80.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[2], -120.f));
}

void Game::Update(float deltaTime)
{
	for (Background& background : backgrounds)
	{
		background.Update(deltaTime);
	}
	for (int i = 0; i < this->player.size(); i++)
	{
		player[i].Update(deltaTime);

		for (size_t k = 0; k < this->player[i].getBullets().size(); k++)
		{
			this->player[i].getBullets()[k].Update();
			if (this->player[i].getBullets()[k].getPosition().x > this->window->getSize().x || this->player[i].getBullets()[k].getPosition().y < 0)
			{
				this->player[i].getBullets().erase(this->player[i].getBullets().begin() + k);
				return;
			}
		}
	}

}

void Game::Draw()
{
	this->window->clear();
	for (Background& background : backgrounds)
	{
		background.Draw(*window);
	}
	for (int i = 0; i < this->player.size(); i++)
	{
		player[i].Draw(*this->window);
	}
	this->window->display();
}
