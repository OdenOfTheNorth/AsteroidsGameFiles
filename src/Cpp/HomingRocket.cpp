#include "HomingRocket.h"

//57.295779512896171867977148875518
HomingRocket::HomingRocket(SDL_Texture* texture,vector<GameObject::CollisionLayers> collisionLayers, CollisionLayers l)
{
	SetCollisionMatrix(collisionLayers);
	layer = l;
	rocketTexture = texture;
	rect.h = rocketSize.y;
	rect.w = rocketSize.x;
	radius = rocketSize.x / 2.2;
}

HomingRocket::~HomingRocket()
{
}

void HomingRocket::Update(Player * player, double deltaTime, double time)
{
	if (Vector2::Distance(position, player->position) > 1)
	{
		forwardDirection = Vector2::Lerp(forwardDirection, Vector2::GetNormalizedDirection(position, player->position), turnSpeed);

		forwardDirection.Normalize();
		//cout << angle << "  " << dir.x << "  " << dir.y << endl;

		angle = Vector2::AngleFromDirection(forwardDirection);

		debugPosition = position + forwardDirection * 60;


		position += forwardDirection * rocketSpeed * deltaTime;
	}
}

void HomingRocket::Render(SDL_Renderer * renderer)
{
	rect.x = round(position.x);
	rect.y = round(position.y);
	SDL_RenderCopyEx(renderer, rocketTexture, NULL, &rect, angle * GameMath::radToDeg() + 90, NULL, SDL_FLIP_NONE);

	SDL_Rect debugRect;
	debugRect.x = position.x;
	debugRect.y = position.y;
	debugRect.w = radius * 2;
	debugRect.h = radius * 2;
	//SDL_RenderFillRect(renderer, &debugRect);
}

void HomingRocket::OnCollision()
{
	isActive = false;
}

void HomingRocket::Init(Vector2 pos, double speed, Player* player)
{
	position = pos;
	rocketSpeed = speed;
	isActive = true;

	forwardDirection = Vector2::GetNormalizedDirection(position, player->position);
	angle = atan2(forwardDirection.y, forwardDirection.x);

}
