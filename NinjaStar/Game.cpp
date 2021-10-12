#include "Game.h"

Game::Game(RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(60);
	this->playerTexture.loadFromFile("Texture/Player/sprite.png");
	this->bulletTexture.loadFromFile("Texture/Player/bullet.png");
	this->enemyTexture.loadFromFile("Texture/Player/starfall.png");
	this->player.push_back(Player(&this->playerTexture, &this->bulletTexture, Vector2u(5, 2), 0.065f));
	for (size_t i = 0; i < 3; i++)
	{
		this->backgroundTexture[i].loadFromFile("Texture/Background/" + to_string(i) + ".png");

	}
	this->backgrounds.push_back(Background(&this->backgroundTexture[0], -60.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[1], -80.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[2], -120.f));

	this->spawnTimerMax = 5.f;
	this->spawnTimer = spawnTimerMax;
}

void Game::Update(float deltaTime)
{
	for (Background& background : backgrounds)
	{
		background.Update(deltaTime);
	}

	if (spawnTimer < spawnTimerMax)
	{
		spawnTimer += deltaTime;
	}
	if (spawnTimer >= spawnTimerMax)
	{
		Vector2f dir = { player[0].getPosition().x - window->getSize().x, player[0].getPosition().y };
		enemies.push_back(Enemy(&this->enemyTexture, dir, 0.2, Vector2f(window->getSize().x, 0), 1, 5, 1, 3));
		cout << "enemy" << spawnTimer << endl;
		spawnTimer = 0;
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
				break;
			}
			for (size_t j = 0; j < enemies.size(); j++)
			{
				if (this->player[i].getBullets()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
				{
					//cout << "player:" << player[i].getBullets()[k].getGlobalBounds().width << " " << player[i].getBullets()[k].getGlobalBounds().height << endl;
					//cout << "enemy:" << enemies[j].getGlobalBounds().width << " " << enemies[j].getGlobalBounds().height << endl;

					player[i].getBullets().erase(player[i].getBullets().begin() + k);
					if (enemies[j].getHp() > 0)
					{
						enemies[j].takeDamage(1);
					}
					if (enemies[j].getHp() <= 0)
					{
						enemies.erase(enemies.begin() + j);
					}
					break;
				}

			}

		}
	}
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update(deltaTime);
		if (enemies[i].getPosition().x <= 0)
		{
			enemies.erase(enemies.begin() + i);
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
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].Draw(*this->window);
	}
	for (int i = 0; i < this->player.size(); i++)
	{
		player[i].Draw(*this->window);
	}
	this->window->display();

}
