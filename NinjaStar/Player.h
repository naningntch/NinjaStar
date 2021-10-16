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
	int hp;
	int hpMax;
	int damage;
	int damageMax;
	int damageTimerMax;
	int damageTimer;

public:
	Player(Texture* texture,Texture *bulletTexture, Vector2u imageCount, float switchTime);
	void takeDamage(int damage);
	void Movement(float deltaTime);
	void Combat(RenderWindow& target);
	void Update(float deltaTime);
	void Draw(RenderWindow& target);

	inline const int getShootTimerMax()const { return this->shootTimerMax; }
	inline const Vector2f& getPosition()const { return this->sprite.getPosition(); }
	inline const FloatRect& getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline vector<Bullet>& getBullets() { return this->bullets; }

	inline int getHp() { return this->hp; }
	inline int getHpMax() { return this->hpMax; }
	inline int getDamage() { return this->damage; }
	

public:
	IntRect uvRect;
	float jumpF = 400;
	float gravityAcceleration = 9.8;

	float mass = 50;
	float speedValue = 0;
	float accelerationValue = 0;

};

