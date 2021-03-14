#pragma once
#include "SDL.h"
#include "Vector2.h"
#include <math.h>
#include "GameMath.h"
#include <iostream>
#include "Bullet.h"
#include "Player.h"
#include "GameObject.h"

class HomingRocket : public GameObject
{
public:
	HomingRocket(SDL_Texture* texture, vector<GameObject::CollisionLayers> collisionLayers, CollisionLayers layer);
	~HomingRocket();

	void Update(Player * player, double deltaTime, double time);
	void Render(SDL_Renderer* renderer);

	void OnCollision();

	void Init(Vector2 pos, double speed, Player* player);
private:
	Vector2 debugPosition;
	Vector2 forwardDirection;

	Vector2 rocketSize = Vector2(50, 50);

	SDL_Texture* rocketTexture;

	double angle;

	double rocketSpeed;
	
	double explodeTime;
	double SpawnTime;

	//Between 0 and 1
	double turnSpeed = 0.02;

	SDL_Rect rect;
};