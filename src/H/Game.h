#pragma once
using namespace std;
#include "SDL.h"
#include <iostream>
#include "Inputs.h"
#include "Player.h"
#include "HazardController.h"
#include <SDL_image.h>
#include <string>
#include "Collision2D.h"
#include <SDL_TTF.h>
#include "RessourceManager.h"
#include "ScoreSystem.h"

class Game
{
public:
	Game(const char* title, int resX, int resY, bool fullscreen);
	~Game();

	void GameLoop();
	void Update();
	void Render();
	double GetTimeSec() { return gameTime / 1000; }

	Inputs* inputs;
	Player* player;
	HazardController* hazardController;

	RessourceManager* ressourceManager;
	ScoreSystem* scoreSystem;

	const double DesiredFps = 60;
	const double msPerSecond = 1000;	
	double gameTime;
	double deltaTime;
	int frameCounter;
private:
	void Reset();

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Color color = { 0,255,0 };
	SDL_Rect textRect;
	SDL_Texture * texture;

	int cycleCount;
	double accumilator = 0;
	double cycleTime;
	double independedGameTime;	
	Collision2D* collsionSystem;


	
	bool isRunning = true;
};