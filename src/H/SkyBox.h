#pragma once
#include "SDL.h"
#include "RessourceManager.h"
#include "Vector2.h"
class SkyBox
{
	public:
		SkyBox(RessourceManager* rM, Vector2 screenSize);
		void Render(SDL_Renderer* renderer);
	private:
		SDL_Texture* skyTexture;
		SDL_Rect rect;

};

