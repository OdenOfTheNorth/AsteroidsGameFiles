#pragma once
#include "SDL.h"
#include "Vector2.h"
#include <math.h>
#include <iostream>
#include "Bullet.h"
#include "Player.h"
#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	Asteroid(SDL_Texture* texture, std::vector<GameObject::CollisionLayers> collisionLayers, CollisionLayers layer);
	~Asteroid();

	void OnCollision();

	void Update(double deltaTime);
	void Render(SDL_Renderer* renderer);

	void Init(Vector2 pos, Vector2 vel, Vector2 gravityAccel, int size, int life);

private:
	int lives = 0;
	double lifeTimer = 0;
	double lifeTime = 10;
	SDL_Texture* AsteroidTexture;
	Vector2 velocity;
	Vector2 gravityAcceleration;
	SDL_Rect rect;
	bool test;
};