#include "Player.h"

Player::Player(Vector2 startPos, Vector2 size, Vector2 screenS, double rad, 
	std::vector<GameObject::CollisionLayers> collisionLayers, 
	CollisionLayers l, Collision2D* cS, RessourceManager* rM)
{
	collisionSystem = cS;
	SetCollisionMatrix(collisionLayers);
	layer = l;
	rect = SDL_Rect();
	startPosition = position = startPos;
	rect.x = startPos.x;
	rect.y = startPos.y;
	rect.w = size.x;
	rect.h = size.y;

	radius = rad;

	texture = rM->PlayerTexture;

	isActive = true;

	if(radius == 0) radius = std::fmin(size.x, size.y);

	screenSize = screenS;
	boostFuel = boostMaxFuel;
}

Player::~Player()
{
	for (int i = 0; i < BulletPoolSize; i++)
	{
		if (bulletList[i] != NULL)
		{
			delete bulletList[i];
		}
	}
}

void Player::Render(SDL_Renderer * renderer)
{
	if (!isActive) return;

	for (int i = 0; i < BulletPoolSize; i++)
	{
		if (bulletList[i] != NULL)
		{
			if (bulletList[i]->isActive) bulletList[i]->Render(renderer);
		}
	}

	rect.x = round(position.x);
	rect.y = round(position.y);

	if(texture == nullptr)
		texture = RenderingUtilities::LoadTexture("Ressources/PlayerRocket.png", renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderCopyEx(renderer, texture , NULL, &rect, 0, NULL, SDL_FLIP_NONE);

	SDL_Rect fuelRect;
	fuelRect.x = 10;
	fuelRect.y = screenSize.y - 30;
	fuelRect.h = 20;
	fuelRect.w = 100 * boostFuel / boostMaxFuel;
	SDL_RenderFillRect(renderer, &fuelRect);

	SDL_Rect lifeRect;
	lifeRect.x = 10;
	lifeRect.y = screenSize.y - 60;
	lifeRect.h = 20;
	lifeRect.w = 20;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	for (int i = 0; i < lives; i++)
	{
		SDL_RenderFillRect(renderer, &lifeRect);
		lifeRect.x += 40;
	}

	//SDL_Rect debugRect;
	//debugRect.x = position.x;
	//debugRect.y = position.y;
	//debugRect.w = radius * 2;
	//debugRect.h = radius * 2;
	//SDL_RenderFillRect(renderer, &debugRect);

}

void Player::UpdatePlayer(Inputs* input, double deltaTime, double time)
{	
	if (lives <= 0 && !isDead)
	{
		isDead = true;
		deathTime = time + deathDelay;
		isActive = false;
	}

	if (isDead && deathTime < time)
	{
		Reset = true;
	}

	if (!isActive) return;
	framesSinceLastHit++;

	bool horizontalMovement = false;
	if (!isGrounded)
	{
		if (input->aDown)
		{
			horizontalMovement = true;
			velocity.x = -speed;
		}
		if (input->dDown)
		{
			horizontalMovement = true;
			velocity.x = speed;
		}
	}

	if (!horizontalMovement)
	{
		velocity.x = 0;
	}

	UpdateBoost(deltaTime, input);

	GravityUpdate();

	Move(deltaTime);

	if (input->kDown && time - lastFireTime > timeBetweenBullets)
	{
		lastFireTime = time;
		Shoot();
	}

	for (int i = 0; i < BulletPoolSize; i++)
	{
		if (bulletList[i] != nullptr)
		{
			if(bulletList[i]->isActive) bulletList[i]->Update(deltaTime);
		}
	}
}

void Player::OnCollision()
{
	if (!isActive) return;

	if (framesSinceLastHit > invincibilityframes)
	{
		framesSinceLastHit = 0;
		lives--;
	}
}

void Player::ResetPlayer()
{
	for (int i = 0; i < BulletPoolSize; i++)
	{
		if (bulletList[i] != nullptr)
		{
			bulletList[i]->isActive = false;
		}
	}

	lives = maxLives;
	position = startPosition;
	isDead = false;
	isActive = true;
	Reset = false;
	velocity = Vector2::Zero();
	boostFuel = boostMaxFuel;
}

void Player::Shoot()
{
	
	for (int i = 0; i < BulletPoolSize; i++)
	{
		if (bulletList[i] == nullptr)
		{
			bulletList[i] = new Bullet(Vector2(0, -1), Vector2(position.x + rect.w / 2, position.y), 10,
				std::vector<CollisionLayers>{ rockets, asteroids }, bullet);

			collisionSystem->AddCollider(bulletList[i]);

			//cout << "true" << endl;
			break;
		}
		else if (!bulletList[i]->isActive)
		{
			bulletList[i]->isActive = true;
			bulletList[i]->position = Vector2(position.x + rect.w / 2 - bulletList[i]->radius / 2, position.y);
			//cout << "true" << endl;
			bulletList[i]->direction = Vector2(0, -1);
			bulletList[i]->lifeTimer = 0;
			break;
		}
	}
}

void Player::UpdateBoost(double deltatime, Inputs* input)
{
	if (input->wDown && boostFuel > 0)
	{
		
		isBoosting = true;
		double extraBoost = 0;
		if (velocity.y > 0) {
			extraBoost = velocity.y;
		}

		//cout << boostFuel << endl;

		boostFuel -= boostConsumption * deltatime;
		velocity.y -= (boostAcceleration + extraBoost);
	}
	else if (!input->wDown)
	{
		isBoosting = false;
		//cout << "Recharge   " << boostFuel << endl;

		if (boostFuel < boostMaxFuel) boostFuel += boostRecharge * deltatime;
	}
	else
	{
		isBoosting = false;
	}

}

void Player::GravityUpdate()
{
	if ((screenSize.y - rect.h) - position.y < groundClearance)
	{
		if (!isGrounded && !isBoosting)
		{
			boostFuel = boostMaxFuel;
			isGrounded = true;
			velocity.y = 0;
		}
	}
	else
	{
		if (!isBoosting) velocity.y += gravityAcceleration;
		isGrounded = false;
	}
}

void Player::Move(double deltaTime)
{
	position += velocity * deltaTime;

	position = Vector2::Clamp(position, Vector2(0, 0), Vector2(screenSize.x - rect.w, screenSize.y - rect.h));

}
