#pragma once
#include "SDL.h"
#include <SDL_TTF.h>
#include <string>
#include "RenderingUtilities.h"
class RessourceManager
{
	public:
		SDL_Texture* PlayerTexture;
		SDL_Texture* AsteroidTexture;
		SDL_Texture* RocketTexture;
		SDL_Texture* RollingStoneTexture;
		SDL_Texture* SkyStoneTexture;

		const std::string scoreFilePath = "Ressources/Score.txt";

		TTF_Font* font;

		void RessourceInit(SDL_Renderer* renderer);

		SDL_Texture* GetText(std::string text, int fontSize, SDL_Color color, SDL_Renderer* renderer);

	private:
		const std::string asteroidTexturePath = "Ressources/Asteroid.png";
		const std::string rocketTexturePath = "Ressources/HomingRocket.png";
		const std::string rollingStoneTexturePath = "Ressources/RollingStones.png";
		const std::string playerTexturePath = "Ressources/PlayerRocket.png";
		const std::string skyTexturePath = "Ressources/SkyTexture.png";

		const std::string fontAPath = "Ressources/ArialCE.ttf";
};

