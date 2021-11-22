#include "Game.h"


Game::Game(RenderWindow* window)
{

	this->window = window;
	this->window->setMouseCursorVisible(false);
	this->window->setFramerateLimit(100);

	this->mouseTexture.loadFromFile("Texture/Player/focus.png");
	this->mouseSprite.setTexture(this->mouseTexture);
	this->mouseSprite.setScale(0.12f, 0.12f);
	this->mouseSprite.setOrigin(Vector2f(this->mouseTexture.getSize().x / 2, this->mouseTexture.getSize().y / 2));

	this->playerTexture.loadFromFile("Texture/Player/sprite.png");
	this->bulletTexture.loadFromFile("Texture/Player/bullet.png");
	this->enemyTexture.loadFromFile("Texture/Player/starfall.png");
	this->itemTexture.loadFromFile("Texture/Player/coin.png");
	this->logoTexture.loadFromFile("Texture/Player/hp.png");
	this->coinIcon.loadFromFile("Texture/Player/icon.png");
	this->scoreIcon.loadFromFile("Texture/Player/icon2.png");
	this->menuTexture.loadFromFile("Texture/Player/menu.png");
	this->gameOverTexture.loadFromFile("Texture/Background/gameOver.png");
	this->buttonTexture[0].loadFromFile("Texture/menu/1.png");
	this->buttonTexture[1].loadFromFile("Texture/menu/2.png");
	this->buttonTexture[2].loadFromFile("Texture/menu/3.png");
	this->buttonTexture[3].loadFromFile("Texture/menu/4.png");
	this->buttonTexture[4].loadFromFile("Texture/menu/5.png");
	this->popupWindowTexture.loadFromFile("Texture/menu/hamburger.png");

	this->popupWindow.setTexture(this->popupWindowTexture);
	this->popupWindow.setPosition(440, 180);

	this->scoreOver.setPosition(720, 440);
	this->scoreOver.setFont(this->font);
	this->scoreOver.setCharacterSize(72);

	this->highScore.setPosition(720, 540);
	this->highScore.setFont(this->font);
	this->highScore.setCharacterSize(72);

	for (size_t i = 0; i < 5; i++)
	{
		this->button[i].setScale(0.35f, 0.35f);
		this->button[i].setTexture(this->buttonTexture[i]);
	}

	this->button[0].setPosition(530, 250);
	this->button[1].setPosition(560, 330);
	this->button[3].setPosition(800, 330);
	this->button[4].setPosition(700, 250);

	this->button[1].setOrigin(buttonTexture[1].getSize().x / 2, buttonTexture[1].getSize().y / 2);
	this->button[3].setOrigin(buttonTexture[3].getSize().x / 2, buttonTexture[3].getSize().y / 2);

	this->multiplierAdderMax = 10;
	this->multiplierAdder = 0;
	this->multiplierTimerMax = 400.f;
	this->multiplierTimer = this->multiplierTimerMax;

	this->scores = 0;
	this->coins = 0;

	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(24);
	this->scoreText.setString(to_string(scores));

	this->coinText.setFont(this->font);
	this->coinText.setCharacterSize(24);
	this->coinText.setString(to_string(coins));

	this->healCooldown = 10.f;
	this->useHeal = false;
	this->usingHeal = false;


	this->invisCooldown = 20.f;
	this->useInvis = false;
	this->usingInvis = false;

	this->menu.setTexture(menuTexture);
	this->menu.setPosition(50, 50);
	this->menu.setOrigin(menuTexture.getSize().x / 2, menuTexture.getSize().y / 2);

	this->gameOver.setSize(Vector2f(this->window->getSize()));
	this->gameOver.setTexture(&this->gameOverTexture);

	this->player.push_back(Player(&this->playerTexture, &this->bulletTexture, Vector2u(5, 2), 0.065f));
	for (size_t i = 0; i < 3; i++)
	{
		this->backgroundTexture[i].loadFromFile("Texture/Background/" + to_string(i) + ".png");

	}

	this->backgrounds.push_back(Background(&this->backgroundTexture[0], -60.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[1], -80.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[2], -120.f));

	this->spawnTimerMax = 100.f;
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

	this->font.loadFromFile("Font/font.ttf");
	initUI();
	initAudio();
}

void Game::initAudio()
{
	this->boomBuffer.loadFromFile("Sound/boom_sfx.wav");
	this->boomSfx.setBuffer(boomBuffer);


	this->shurikenBuffer.loadFromFile("Sound/shuriken_sfx.wav");
	this->shurikenSfx.setBuffer(shurikenBuffer);


	this->coinBuffer.loadFromFile("Sound/coin_sfx.wav");
	this->coinSfx.setBuffer(coinBuffer);


	this->healBuffer.loadFromFile("Sound/heal_sfx.wav");
	this->healSfx.setBuffer(healBuffer);

	this->invisibleBuffer.loadFromFile("Sound/invisible_sfx.wav");
	this->invisibleSfx.setBuffer(invisibleBuffer);

	this->getdmgBuffer.loadFromFile("Sound/getdmg_sfx.wav");
	this->getdmgSfx.setBuffer(getdmgBuffer);

	this->buttonBuffer.loadFromFile("Sound/button_sfx.wav");
	this->buttonSfx.setBuffer(buttonBuffer);

}

void Game::initUI()
{
	this->coin.setTexture(this->coinIcon);
	this->coin.setPosition(1345, 55);
	this->coin.setOrigin(coinIcon.getSize().x, coinIcon.getSize().y / 2.f);
	this->score.setTexture(this->scoreIcon);
	this->score.setPosition(1345, 130);
	this->score.setOrigin(scoreIcon.getSize().x, scoreIcon.getSize().y / 2.f);

	this->skillTexture[0].loadFromFile("Texture/Player/skill2.png");
	this->skill[0].setTexture(this->skillTexture[0]);
	this->skillTexture[1].loadFromFile("Texture/Player/skill1.png");
	this->skill[1].setTexture(this->skillTexture[1]);
	this->skill[0].setPosition(1280, 170);
	this->skill[0].setScale(0.3f, 0.3f);
	this->skill[1].setPosition(1280, 232);
	this->skill[1].setScale(0.3f, 0.3f);

	this->heal.setPosition(1302, 180);
	this->heal.setFont(this->font);
	this->heal.setCharacterSize(25);

	this->invisible.setPosition(1298, 242);
	this->invisible.setFont(this->font);
	this->invisible.setCharacterSize(25);

}


void Game::UpdatePlayerUI(int index)
{
	this->hpBar[1].setSize(Vector2f(player.at(index).getHp() * 500 / player.at(index).getHpMax(), hpBar[0].getSize().y));
}

void Game::Update(float deltaTime)
{
	this->mouseSprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(*this->window)));
	//gamestart
	if (this->playerAlive && !this->popupState)
	{
		for (Background& background : backgrounds)
		{
			background.Update(deltaTime);
		}

		if (spawnTimer < spawnTimerMax)
		{
			spawnTimer++;
		}

		if (this->multiplierTimer > 0.f)
		{
			this->multiplierTimer--;
			if (this->multiplierTimer <= 0.f)
			{
				this->multiplierTimer = 0.f;
				this->multiplierAdder = 0;
				this->scoreMultiplier = 1;
			}
		}

		this->scoreMultiplier = this->multiplierAdder / this->multiplierAdderMax + 1;
		if (spawnTimer >= spawnTimerMax)
		{

			Vector2f randPos = Vector2f(rand() % window->getSize().x, 0);
			enemies.push_back(Enemy(&this->enemyTexture, player.at(0).getPosition(), 400.f, randPos, 1, 3, 1, 3));
			spawnTimer = 0;

		}

		for (int i = 0; i < this->player.size(); i++)
		{
			player.at(i).Update(deltaTime);

			//player use invisible
			if (player.at(i).useInvisible() && !this->useInvis && coins >= 15)
			{
				invisibleSfx.play();
				useInvis = true;
				coins -= 15;
			}

			//player use heal
			if (player.at(i).useHeal() && !this->useHeal && coins >= 10)
			{
				healSfx.play();
				useHeal = true;
				coins -= 10;
			}

			//delete coin when get off screen
			for (size_t j = 0; j < items.size(); j++)
			{
				items.at(j).Update(deltaTime);
				if (items.at(j).getPosition().x <= 0)
				{
					items.erase(items.begin() + j);
					break;
				}
				//player get coin
				if (items.at(j).getGlobalBounds().intersects(player.at(i).getGlobalBounds()))
				{
					coins++;
					coinSfx.play();
					items.erase(items.begin() + j);
					break;
				}
			}

			for (size_t l = 0; l < enemies.size(); l++)
			{
				enemies.at(l).Update(deltaTime);

				//delete when meteor out of screen
				if (enemies.at(l).getPosition().x <= 0 || enemies.at(l).getPosition().x >= 1366)
				{
					enemies.erase(enemies.begin() + l);
					break;
				}

				//meteor intersect player
				if (this->enemies.at(l).getGlobalBounds().intersects(this->player.at(i).getGlobalBounds()) && !this->usingInvis)
				{
					getdmgSfx.play();
					int damage = enemies.at(l).getDamage();
					player.at(i).takeDamage(damage);
					if (player.at(i).getHp() <= 0)
					{
						this->playerAlive = false;
						if (coins == 0)
							coins = 1;
						size_t lastScore = scores * coins;
						scoreOver.setString(to_string(lastScore));
					}
					enemies.erase(enemies.begin() + l);
					break;
				}

			}

			for (size_t k = 0; k < this->player.at(i).getBullets().size(); k++)
			{
				this->shurikenSfx.play();

				//player shoot star

				this->player.at(i).getBullets().at(k).Update();
				if (this->player.at(i).getBullets().at(k).getPosition().x > this->window->getSize().x || this->player.at(i).getBullets().at(k).getPosition().y < 0 || this->player.at(i).getBullets().at(k).getPosition().y > window->getSize().y)
				{
					this->player.at(i).getBullets().erase(this->player.at(i).getBullets().begin() + k);
					break;
				}

				for (size_t j = 0; j < enemies.size(); j++)
				{
					//meteor get star
					if (this->player.at(i).getBullets().at(k).getGlobalBounds().intersects(this->enemies.at(j).getGlobalBounds()))
					{
						player.at(i).getBullets().erase(player.at(i).getBullets().begin() + k);
						if (enemies.at(j).getHp() > 0)
						{
							int damage = player.at(i).getDamage();
							enemies.at(j).takeDamage(damage);
						}

						//enemy dead
						if (enemies.at(j).getHp() <= 0)
						{
							this->boomSfx.play();
							scores += enemies.at(j).getHpMax() * scoreMultiplier;
							items.push_back(Item(&this->itemTexture, Vector2u(3, 2), 0.1f, this->enemies.at(j).getPosition()));
							enemies.erase(enemies.begin() + j);
							if (spawnTimerMax > 25.f)
								spawnTimerMax -= 0.05f;
						}
						break;
					}

				}

			}

		}
		this->scoreText.setPosition(this->score.getPosition().x - 28.f, this->score.getPosition().y + 2);
		this->scoreText.setOrigin(this->scoreText.getLocalBounds().width, this->scoreText.getLocalBounds().height / 2);
		this->scoreText.setString(to_string(scores));

		this->coinText.setPosition(this->coin.getPosition().x - 28.f, this->coin.getPosition().y - 5);
		this->coinText.setOrigin(this->coinText.getLocalBounds().width, this->coinText.getLocalBounds().height / 2);
		this->coinText.setString(to_string(coins));

		if (useInvis)
		{
			invisCooldown -= deltaTime;
			invisible.setString(to_string(int(invisCooldown)));
			skill[1].setColor(Color(255, 255, 255, 100));

			if (invisCooldown <= 15.f)
			{
				usingInvis = false;
			}
			else
			{
				usingInvis = true;
				for (size_t i = 0; i < player.size(); i++)
				{
					player.at(i).SetColorOpa();

				}
			}
			if (invisCooldown <= 1.f)
			{
				useInvis = false;
				invisCooldown = 20;
				invisible.setString(" ");
				skill[1].setColor(Color::White);
			}
		}

		if (useHeal)
		{
			healCooldown -= deltaTime;
			heal.setString(to_string(int(healCooldown)));
			skill[0].setColor(Color(255, 255, 255, 100));

			if (healCooldown <= 8.f)
			{
				usingHeal = false;
			}
			else
			{
				usingHeal = true;
				for (size_t i = 0; i < player.size(); i++)
				{
					player.at(i).heal();
				}
			}

			if (healCooldown <= 1.f)
			{
				useHeal = false;
				healCooldown = 15;
				heal.setString(" ");
				skill[0].setColor(Color::White);
			}

		}

	}
	if (menu.getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
	{
		menu.setScale(0.18f, 0.18f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			buttonSfx.play();
			popupState = true;

		}
	}
	else
	{
		menu.setScale(0.15f, 0.15f);
	}

	if (button[1].getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
	{
		button[1].setScale(0.38f, 0.38f);
		if (Mouse::isButtonPressed(Mouse::Left) && popupState)
		{
			buttonSfx.play();
			popupState = false;
		}
	}
	else
	{
		button[1].setScale(0.35f, 0.35f);
	}

	if (button[3].getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
	{
		button[3].setScale(0.38f, 0.38f);
		if (Mouse::isButtonPressed(Mouse::Left) && popupState)
		{
			buttonSfx.play();
			menuState = true;
			if (!scoreAdd)
			{
				Score score(this->window);
				score.writeFile(this->playerName, scores * coins);

				scoreAdd = true;
			}
		}
	}
	else
	{
		button[3].setScale(0.35f, 0.35f);
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

	this->window->draw(this->skill[0]);
	this->window->draw(this->skill[1]);
	this->window->draw(this->heal);
	this->window->draw(this->invisible);
	this->window->draw(this->coin);
	this->window->draw(this->coinText);
	this->window->draw(this->score);
	this->window->draw(this->scoreText);
	this->window->draw(this->menu);
	if (!playerAlive)
	{
		GameOver();
	}
	if (this->popupState)
	{
		this->window->draw(this->popupWindow);
		this->window->draw(this->button[1]);
		this->window->draw(this->button[3]);
	}

	this->window->draw(this->mouseSprite);
	this->window->display();

}

void Game::GameOver()
{
	if (!scoreAdd)
	{
		Score score(this->window);
		score.writeFile(this->playerName, scores * coins);

		scoreAdd = true;
		highScore.setString(to_string(score.highRead()));
	}


	if (button[0].getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
	{
		button[0].setScale(0.38f, 0.38f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			buttonSfx.play();
			GameReset();
		}

	}
	else
	{
		button[0].setScale(0.35f, 0.35f);
	}

	if (button[4].getGlobalBounds().contains(Vector2f(Mouse::getPosition())))
	{
		button[4].setScale(0.38f, 0.38f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			buttonSfx.play();
			menuState = true;
		}


	}
	else
	{
		button[4].setScale(0.35f, 0.35f);
	}
	this->window->draw(this->gameOver);
	this->window->draw(this->button[0]);
	this->window->draw(this->button[4]);
	this->window->draw(this->scoreOver);
	this->window->draw(this->highScore);
}

void Game::GameReset()
{
	scoreAdd = false;
	enemies.clear();
	for (size_t i = 0; i < player.size(); i++)
	{
		player[i].getBullets().clear();
	}
	player.clear();
	items.clear();
	backgrounds.clear();
	this->popupState = false;
	this->playerAlive = true;

	this->multiplierAdderMax = 10;
	this->multiplierAdder = 0;
	this->multiplierTimerMax = 400.f;
	this->multiplierTimer = this->multiplierTimerMax;

	this->scores = 0;
	this->coins = 0;

	this->healCooldown = 1.f;
	this->useHeal = false;
	this->usingHeal = false;


	this->invisCooldown = 1.f;
	this->useInvis = false;
	this->usingInvis = false;

	this->spawnTimerMax = 100.f;
	this->spawnTimer = spawnTimerMax;
	this->player.push_back(Player(&this->playerTexture, &this->bulletTexture, Vector2u(5, 2), 0.065f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[0], -60.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[1], -80.f));
	this->backgrounds.push_back(Background(&this->backgroundTexture[2], -120.f));

}

