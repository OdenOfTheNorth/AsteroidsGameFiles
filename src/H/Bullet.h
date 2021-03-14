#pragma once
#pragma once
#include "SDL.h"
#include "Vector2.h"
#include <math.h>
#include <iostream>
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(Vector2 dir, Vector2 startPos,int rad,std::vector<CollisionLayers> collisionLayers, CollisionLayers layer);
	~Bullet();

	void OnCollision();

	void Render(SDL_Renderer* renderer);
	void Update(double deltaTime);
	Vector2 direction;
	double lifeTimer = 0;

private:
	const double bulletSpeed = 1000;
	const double lifeTime = 10;
	SDL_Rect rect;
};

