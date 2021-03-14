#include "GameObject.h"

GameObject::GameObject()
{
	//radius = 10;
}

GameObject::GameObject(Vector2 pos, double rad)
{
	position = pos;
	radius = rad;
}

Vector2 GameObject::GetRealPosition()
{
	return Vector2(position.x + radius, position.y + radius);
}

void GameObject::SetRealPosition(Vector2 pos)
{
	position = Vector2(pos.x - radius, pos.y - radius);
}

void GameObject::OnCollision()
{
}

void GameObject::SetCollisionMatrix(std::vector<CollisionLayers> layers)
{
	for (int i = 0; i < layers.size(); i++)
	{
		collisionMatrix |= layers[i];
	}
}

GameObject::~GameObject()
{
}
