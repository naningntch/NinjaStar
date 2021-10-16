#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"
#include"SFML/Window.hpp"

using namespace std;
using namespace sf;

class Enemy
{
private:
	Texture* texture;
	Vector2f playerPos;
	Sprite sprite;
	float speed;
	Vector2f position;
	int hp;
	int hpMax;
	int damage;
	int damageMax;
	double radians;

public:
	Enemy(Texture* texture, Vector2f playerPos, float speed, Vector2f position, int hp, int hpMax, int damage, int damageMax);
	void Update(float deltaTime);
	void Draw(RenderTarget& target);

	inline int getHp()
	{
		return rand() % this->hpMax + this->hp;
	}

	inline int getDamage()
	{
		return rand() % this->damageMax + this->damage;
	}
	
	void takeDamage(int damage);
	inline const Vector2f getPosition()const { return this->sprite.getPosition(); }
	inline const FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
};

