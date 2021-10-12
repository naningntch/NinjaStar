#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2f dir, float speed, Vector2f position, int hp, int hpMax, int damage, int damageMax)
{
	this->texture = texture;
	this->dir = dir;
	this->speed = speed;
	this->sprite.setTexture(*this->texture);
	this->position = position;
	this->sprite.setPosition(this->position);
	this->sprite.setScale(0.25, 0.25);
	this->sprite.rotate(45.f);
	this->hp = hp;
	this->hpMax = hpMax;
	this->damage = damage;
	this->damageMax = damageMax;

}

void Enemy::Update(float deltaTime)
{
	float a = vectorLength(this->dir);
	Vector2f b = normalize(this->dir, a);
	this->sprite.move(dir.x * speed * deltaTime, dir.y * speed * deltaTime);
}

void Enemy::Draw(RenderTarget& target)
{
	target.draw(sprite);

}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;

}
