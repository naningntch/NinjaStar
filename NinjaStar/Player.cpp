#include "Player.h"

Player::Player(Texture* texture, Texture* bulletTexture, Vector2u imageCount, float switchTime)
{
	//Sprite Setting
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	this->totalTime = 0.0f;
	this->currentImage.x = 0;
	this->currentImage.y = 1;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.5f, 0.5f);
	this->sprite.setPosition(Vector2f(0.f, 550.f));
	this->bulletTexture = bulletTexture;
	this->shootTimerMax = 25;
	this->shootTimer = this->shootTimerMax;

}

void Player::Movement(float deltaTime)
{

	if (Keyboard::isKeyPressed(Keyboard::Key::W) && !this->jump)
	{
		accelerationValue = jumpF / mass;
		this->jump = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A) && this->sprite.getPosition().x > 10.f)
	{
		this->sprite.move(-200 * deltaTime, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D) && this->sprite.getPosition().x < 1366.f - this->sprite.getGlobalBounds().width)
	{
		this->sprite.move(200 * deltaTime, 0);
	}
	if (this->jump)
	{
		accelerationValue -= gravityAcceleration * deltaTime;
		this->sprite.move(0, -accelerationValue);
		if (this->sprite.getPosition().y > 550)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, 550);
			this->jump = false;
			accelerationValue = 0;
		}
	}

}

void Player::Combat(RenderTarget& target)
{
	if (Mouse::isButtonPressed(Mouse::Left) && this->shootTimer >= this->shootTimerMax)
	{
		this->PlayerPos = Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width, this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2);
		this->MousePos = Vector2f(Mouse::getPosition());
		this->aimDir = MousePos - PlayerPos;
		this->aimDirNorm = aimDir / sqrt((aimDir.x * aimDir.x + aimDir.y * aimDir.y));
		this->bullets.push_back(Bullet(bulletTexture, this->sprite.getPosition(), aimDirNorm, Vector2f(20.0f, 20.0f)));
		this->shootTimer = 0;

	}
}


void Player::Update(float deltaTime)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
	this->sprite.setTextureRect(uvRect);
	if (this->shootTimer < this->shootTimerMax)
	{
		this->shootTimer++;
	}
	Movement(deltaTime);
}

void Player::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
	Combat(target);

}
