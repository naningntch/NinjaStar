#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
using namespace std;
using namespace sf;

class Item
{
private:
	Texture* texture;
	Sprite sprite;

	Vector2u imageCount;
	Vector2u currentImage;
	Vector2f position;

	float totalTime;
	float switchTime;

public:
	Item(Texture* texture, Vector2u imageCount, float switchTime, Vector2f position);
	void Movement(float deltatime);
	void Update(float deltaTime);
	void Draw(RenderTarget& target);
	IntRect uvRect;
	inline const Vector2f getPosition()const { return this->sprite.getPosition(); }
	inline const FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
};

