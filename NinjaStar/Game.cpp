#include "Game.h"

Game::Game(RenderWindow* window)
{

	this->window = window;
	this->window->setMouseCursorVisible(false);
	this->window->setFramerateLimit(100);

	this->mouseTexture.loadFromFile("Texture/Player/focus.png");
	this->mouseSprite.setTexture(this->mouseTexture);
	this->mouseSprite.setScale(0.12f,0.12f);
	this->mouseSprite.setOrigin(Vector2f(this->mouseTexture.getSize().x / 2, this->mouseTexture.getSize().y / 2));

	this->playerTexture.loadFromFile("Texture/Player/sprite.png");
	this->bulletTexture.loadFromFile("Texture/Player/bullet.png");
	this->enemyTexture.loadFromFile("Texture/Player/starfall.png");
	this->itemTexture.loadFromFile("Texture/Player/coin.png");
	this->logoTexture.loadFromFile("Texture/Player/hp.png");

	this->player.push_back(Player(&this->playerTexture, &this->bulletTexture, Vector2u(5, 2), 0.065f));
	for (size_t i = 0; i < 3; i++)
	{
		this->backgroundTexture[i].loadFromFile("Texture/Background/" + to_string(i) + ".png");

	}

	this->backgrounds.push_back(Background(&this->backgroundTexture[0], -60.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[1], -80.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[2], -120.f));

	this->spawnTimerMax = 1.5;
	this->spawnTimer = spawnTimerMax;
	for (size_t i = 0; i < 2; i++)
	{
		this->hpBar[i].setSize(Vector2f(500, 20));
		this->hpBar[i].setPosition(483, 50);
	}
	this->hpBar[1].setFillColor(Color::Green);
	this->logo.setTexture(&this->logoTexture);
	this->logo.setRadius(40);
	this->logo.setPosition(405, 20);

}

void Game::UpdatePlayerUI(int index)
{
	this->hpBar[1].setSize(Vector2f(player.at(index).getHp() * 500 / player.at(index).getHpMax(), hpBar[0].getSize().y));
}

void Game::Update(float deltaTime)
{
	if (this->playerAlive)
	{
		this->mouseSprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(*this->window)));
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

			if (player.at(0).getPosition().x <= window->getSize().x / 2)
				randPos = Vector2f(window->getSize().x, 0);
			enemies.push_back(Enemy(&this->enemyTexture, player.at(0).getPosition(), 400.f, randPos, 1, 5, 1, 3));
			spawnTimer = 0;

		}

		for (int i = 0; i < this->player.size(); i++)
		{
			player.at(i).Update(deltaTime);
			for (size_t j = 0; j < items.size(); j++)
			{
				items.at(j).Update(deltaTime);
				if (items.at(j).getPosition().x <= 0)
				{
					items.erase(items.begin() + j);
					break;
				}
				if (items.at(j).getGlobalBounds().intersects(player.at(i).getGlobalBounds()))
				{
					items.erase(items.begin() + j);
					break;
				}
			}

			for (size_t l = 0; l < enemies.size(); l++)
			{
				enemies.at(l).Update(deltaTime);

				if (enemies.at(l).getPosition().x <= 0 || enemies.at(l).getPosition().x >= 1366)
				{
					enemies.erase(enemies.begin() + l);
					break;
				}

				if (this->enemies.at(l).getGlobalBounds().intersects(this->player.at(i).getGlobalBounds()))
				{
					int damage = enemies.at(l).getDamage();
					player.at(i).takeDamage(damage);
					if (player.at(i).getHp() <= 0)
					{
						this->playerAlive = false;
					}
					enemies.erase(enemies.begin() + l);
					break;
				}

			}

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
							int damage = player.at(i).getDamage();
							enemies.at(j).takeDamage(damage);
						}
						if (enemies.at(j).getHp() <= 0)
						{
							items.push_back(Item(&this->itemTexture, Vector2u(3, 2), 0.1f, this->enemies.at(j).getPosition()));
							enemies.erase(enemies.begin() + j);
						}
						break;
					}

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
		enemies.at(i).Draw(*this->window);
	}
	for (int i = 0; i < this->player.size(); i++)
	{
		player.at(i).Draw(*this->window);
		UpdatePlayerUI(i);
		for (size_t j = 0; j < 2; j++)
		{
			this->window->draw(this->hpBar[j]);
		}
		this->window->draw(this->logo);

	}
	for (int i = 0; i < this->items.size(); i++)
	{
		items.at(i).Draw(*this->window);
	}
	this->window->draw(this->mouseSprite);
	this->window->display();



}
