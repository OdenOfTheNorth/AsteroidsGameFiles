#include "Asteroid.h"

Asteroid::Asteroid(SDL_Texture* texture, std::vector<GameObject::CollisionLayers> collisionLayers, CollisionLayers l)
{
	SetCollisionMatrix(collisionLayers);
	layer = l;
	AsteroidTexture = texture;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update(double deltaTime)
{
	lifeTimer += deltaTime;
	if (lifeTimer > lifeTime)
	{
		isActive = false;
	}

	velocity += gravityAcceleration;
	position += velocity * deltaTime; 
}

void Asteroid::OnCollision()
{
	lives--;
	if(lives <= 0) isActive = false;
}

void Asteroid::Render(SDL_Renderer * renderer)
{	
	rect.x = round(position.x);
	rect.y = round(position.y);
	SDL_RenderCopyEx(renderer, AsteroidTexture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);

	SDL_Rect debugRect;
	debugRect.x = position.x;
	debugRect.y = position.y;
	debugRect.w = radius * 2;
	debugRect.h = radius * 2;
	//SDL_RenderFillRect(renderer, &debugRect);

}

void Asteroid::Init(Vector2 pos, Vector2 vel, Vector2 gravityAccel, int size, int life)
{
	lives = life;
	radius = size / 2.5;
	rect.w = rect.h = size;
	position = pos;
	velocity = vel;
	gravityAcceleration = gravityAccel;
	lifeTimer = 0;
	isActive = true;
}
