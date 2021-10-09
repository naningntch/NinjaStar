#pragma once
#include "Bullet.h"
class Player
{
private:
	Texture* texture;
	Sprite sprite;

	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime;
	float switchTime;
	bool jump = false;

	vector <Bullet> bullets;
	Texture* bulletTexture;
	Vector2f aimDir;
	Vector2f aimDirNorm;
	Vector2f MousePos;
	Vector2f PlayerPos;
	int shootTimer;
	int shootTimerMax;

public:
	Player(Texture* texture,Texture *bulletTexture, Vector2u imageCount, float switchTime);
	void Movement(float deltaTime);
	void Combat(RenderTarget& target);
	void Update(float deltaTime);
	void Draw(RenderTarget& target);

	inline const int getShootTimerMax()const { return this->shootTimerMax; }
	inline const Vector2f& getPosition()const { return this->sprite.getPosition(); }
	inline const FloatRect& getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline vector<Bullet>& getBullets() { return this->bullets; }

public:
	IntRect uvRect;
	float jumpF = 400;
	float gravityAcceleration = 9.8;

	float mass = 45;
	float speedValue = 0;
	float accelerationValue = 0;
};

