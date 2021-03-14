#include "RollingStone.h"

RollingStone::RollingStone(SDL_Texture * texture, vector<GameObject::CollisionLayers> collisionLayers, CollisionLayers l)
{
	rockTexture = texture;
	SetCollisionMatrix(collisionLayers);
	layer = l;
}

RollingStone::~RollingStone()
{
}

void RollingStone::Update(double deltaTime, double time, Vector2 screenSize)
{
	if (direction.x > 0 && position.x > screenSize.x)
	{
		direction = -direction;
	}
	else if(direction.x < 0 && position.x < 0)
	{
		direction = -direction;
	}

	position += direction * (rockSpeed * deltaTime);
	angle += rotationSpeed * direction.x * deltaTime;
}

void RollingStone::Render(SDL_Renderer * renderer)
{
	rect.x = round(position.x);
	rect.y = round(position.y);

	SDL_RenderCopyEx(renderer, rockTexture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);

}

void RollingStone::OnCollision()
{
	cout << "Coll" << endl;
	isActive = false;
}

void RollingStone::Init(Vector2 pos, double speed, Vector2 moveDirection, double rad)
{
	radius = rad;
	position = pos;
	direction = moveDirection;
	rockSpeed = speed;
	isActive = true;
	rect.h = rect.w = rad * 2;
}
