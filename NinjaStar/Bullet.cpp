#include "Bullet.h"

Bullet::Bullet(Texture* texture, Vector2f position, Vector2f dir, Vector2f maxVelocity)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->maxVelocity = maxVelocity;
	this->sprite.setScale(Vector2f(0.1f,0.1f));
	this->sprite.setPosition(position);
	this->dir = dir;
}

void Bullet::Movement()
{
	this->sprite.move(this->maxVelocity.x*dir.x, this->maxVelocity.y * dir.y);
}

void Bullet::Update()
{
	Movement();
}

void Bullet::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
}
