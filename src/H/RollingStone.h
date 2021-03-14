#pragma once
using namespace std;
#include "SDL.h"
#include "Vector2.h"
#include <math.h>
#include "GameMath.h"
#include <iostream>
#include "GameObject.h"

class RollingStone : public GameObject
{
public:
	RollingStone(SDL_Texture* texture, vector<GameObject::CollisionLayers> collisionLayers, CollisionLayers layer);
	~RollingStone();

	void Update(double deltaTime, double time, Vector2 screenSize);
	void Render(SDL_Renderer* renderer);

	void OnCollision();

	void Init(Vector2 pos, double speed, Vector2 moveDirection, double rad);

private:
	double angle;
	double rotationSpeed = 360;
	double rockSpeed;
	Vector2 direction;

	SDL_Texture* rockTexture;

	SDL_Rect rect;
};

