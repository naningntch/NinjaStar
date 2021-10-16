#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
using namespace std;
using namespace sf;

class Bullet
{
private:
	Texture* texture;
	Sprite sprite;
	Vector2f maxVelocity;
	Vector2f dir;

public:
	Bullet(Texture *texture,Vector2f position, Vector2f dir, Vector2f maxVelocity);
	inline const FloatRect& getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }


	void Movement();
	void Update();
	void Draw(RenderTarget & target);
};

