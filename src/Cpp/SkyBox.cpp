
#include "SkyBox.h"

SkyBox::SkyBox(RessourceManager* rM, Vector2 screenSize)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = screenSize.x;
	rect.h = screenSize.y;

	skyTexture = rM->SkyStoneTexture;
}

void SkyBox::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, skyTexture, NULL, &rect);
}
