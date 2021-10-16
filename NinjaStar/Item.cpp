#include "Item.h"

Item::Item(Texture* texture, Vector2u imageCount, float switchTime, Vector2f position)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	this->totalTime = 0.0f;
	this->currentImage.x = 0;
	this->currentImage.y = 1;
	this->position = position;
	this->sprite.setPosition(this->position);
	this->sprite.setScale(0.15f,0.15f);

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Item::Movement(float deltatime)
{
	float dirY = 0;
	if (this->sprite.getPosition().y < 680)
	{
		dirY = 100.f * deltatime;
	}

	this->sprite.move(-100.f * deltatime, dirY);

}

void Item::Update(float deltaTime)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
			currentImage.y++;
			currentImage.y %= 2;
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
	this->sprite.setTextureRect(uvRect);
	Movement(deltaTime);

}

void Item::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
}
