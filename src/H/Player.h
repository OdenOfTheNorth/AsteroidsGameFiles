#pragma once
#include "SDL.h"
#include "Vector2.h"
#include "Inputs.h"
#include <math.h>
#include <iostream>
#include "Bullet.h"
#include "RessourceManager.h"
#include "GameObject.h"
#include "Collision2D.h"
#include <SDL_TTF.h>

class Player : public GameObject
{
public:
	Player(Vector2 startPos, Vector2 size, Vector2 screenS, double rad, 
		std::vector<CollisionLayers> collisionLayers, 
		CollisionLayers layer, Collision2D* cS, RessourceManager* rM);

	~Player();

	void Render(SDL_Renderer* renderer);
	void UpdatePlayer(Inputs* input, double deltaTime, double time);

	void OnCollision();
	
	static const int BulletPoolSize = 1000;
	Bullet* bulletList[BulletPoolSize];

	Collision2D* collisionSystem;

	void ResetPlayer();
	bool Reset = false;
private:

	int lives = 3;
	int maxLives = 3;

	SDL_Rect rect;	
	const double speed = 200;
	Vector2 screenSize;

	void UpdateBoost(double time, Inputs* input);
	void GravityUpdate();
	void Move(double deltaTime);
	void Shoot();

	Vector2 velocity;

	const double gravityAcceleration = 20;
	double gravity = 0;
	double groundClearance = 2;
	bool isGrounded = false;

	const double boostAcceleration = 5;
	double boostMaxFuel = 20;
	double boostFuel = 0;
	double boostConsumption = 2;
	double boostRecharge = 1.5;
	bool isBoosting = false;

	double lastFireTime = 0;
	double timeBetweenBullets = 0.2f;

	int invincibilityframes = 20;
	int framesSinceLastHit = 0;

	bool isDead = false;
	double deathDelay = 2;
	double deathTime;

	Vector2 startPosition;

	SDL_Texture* texture;

};
