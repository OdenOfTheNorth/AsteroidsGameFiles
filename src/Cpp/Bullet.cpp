#include "Bullet.h"

Bullet::Bullet(Vector2 dir, Vector2 startPos,int rad, std::vector<CollisionLayers> collisionLayers, CollisionLayers l)
{
	SetCollisionMatrix(collisionLayers);
	layer = l;	
	rect.h = rect.w = radius = rad;
	position = Vector2(startPos.x + radius / 2, startPos.y);
	//std::cout << radius << std::endl;
	direction = dir;
}

Bullet::~Bullet()
{
}

void Bullet::OnCollision()
{
	isActive = false;
}



void Bullet::Render(SDL_Renderer * renderer)
{
	//std::cout << rect.w << std::endl;
	//std::cout << position.y << " , " << position.x << std::endl;
	rect.x = round(position.x);
	rect.y = round(position.y);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Bullet::Update(double deltaTime)
{	
	position += direction * (bulletSpeed * deltaTime);
	lifeTimer += deltaTime;
	if (lifeTimer > lifeTime)
	{
		isActive = false;
	}
}
