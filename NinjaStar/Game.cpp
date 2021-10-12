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

	this->spawnTimerMax = 1;
	this->spawnTimer = spawnTimerMax;
}

void Game::Update(float deltaTime)
{
	if (this->playerAlive)
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
			Vector2f randPos = Vector2f(0, 0);
			cout << "x" << endl;

			if (player.at(0).getPosition().x <= window->getSize().x / 2)
				randPos = Vector2f(window->getSize().x, 0);
			cout << "y" << endl;

			Vector2f dir = { player.at(0).getPosition().x - window->getSize().x, player.at(0).getPosition().y };
			enemies.push_back(Enemy(&this->enemyTexture, dir, 0.2f, randPos, 1, 5, 1, 3));
			spawnTimer = 0;

		}

		for (int i = 0; i < this->player.size(); i++)
		{
			player[i].Update(deltaTime);

			for (size_t k = 0; k < this->player.at(i).getBullets().size(); k++)
			{

				this->player.at(i).getBullets().at(k).Update();
				if (this->player.at(i).getBullets().at(k).getPosition().x > this->window->getSize().x || this->player.at(i).getBullets().at(k).getPosition().y < 0 || this->player.at(i).getBullets().at(k).getPosition().y > window->getSize().y)
				{
					this->player.at(i).getBullets().erase(this->player.at(i).getBullets().begin() + k);
					break;
				}
				for (size_t j = 0; j < enemies.size(); j++)
				{
					if (this->player.at(i).getBullets().at(k).getGlobalBounds().intersects(this->enemies.at(j).getGlobalBounds()))
					{
						player.at(i).getBullets().erase(player.at(i).getBullets().begin() + k);
						if (enemies.at(j).getHp() > 0)
						{
							enemies.at(j).takeDamage(1);
						}
						if (enemies.at(j).getHp() <= 0)
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
				break;
			}
			for (size_t j = 0; j < player.size(); j++)
			{
				if (this->enemies[i].getGlobalBounds().intersects(this->player[i].getGlobalBounds()))
				{
					int damage = enemies[i].getDamage();
					player[i].takeDamage(damage);
					if (player[i].getHp() <= 0)
					{
						this->playerAlive = false;
					}
					enemies.erase(enemies.begin() + i);
					break;
				}
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
