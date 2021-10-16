#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2f playerPos, float speed, Vector2f position, int hp, int hpMax, int damage, int damageMax)
{
	this->texture = texture;
	this->playerPos = playerPos;
	this->speed = speed;
	this->sprite.setTexture(*this->texture);
	this->position = position;
	this->sprite.setPosition(this->position);
	this->sprite.setScale(0.25, 0.25);

	this->hp = hp;
	this->hpMax = hpMax;
	this->damage = damage;
	this->damageMax = damageMax;

}

void Enemy::Update(float deltaTime)
{
	this->radians = atan2(playerPos.y + 50.f - position.y, playerPos.x - position.x);
	sprite.move(deltaTime * speed * cos(this->radians), deltaTime * speed * sin(radians));
	sprite.setRotation((radians * 180 / M_PI) - 100);
}

void Enemy::Draw(RenderTarget& target)
{
	target.draw(sprite);

}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;

}
