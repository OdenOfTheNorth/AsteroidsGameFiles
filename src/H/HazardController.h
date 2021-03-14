#pragma once
#include "Asteroid.h"
#include "HomingRocket.h"
#include "Player.h"
#include "Collision2D.h"
#include "RollingStone.h"
#include <time.h>
#include "RessourceManager.h"


class HazardController
{
public:
	HazardController(double delayStart, Player* p, Vector2 screen, SDL_Renderer* rend, Collision2D* col, RessourceManager* rM);
	~HazardController();

	void Update(double deltaTime, double time);
	void Render(SDL_Renderer* renderer);

	void ResetHazards();

private:

	void spawnHazards();
	void spawnAsteroid();
	void spawnRocket();
	void spawnRollingStones();

	int GetRandom(int min, int max);

	static const int asteroidPoolSize = 1000;
	Asteroid* asteroids[asteroidPoolSize];

	static const int homingRocketPoolSize = 1000;
	HomingRocket* homingRockets[homingRocketPoolSize];

	static const int rollingStonePoolSize = 1000;
	RollingStone* rollingStones[rollingStonePoolSize];

	double difficultyIncreaseIntervals = 5;
	double difficultySpawntimeDecrease = 0.05;
	double nextDifficultyIncreaseTime = 0;
	double minSpawnDelay = 0.01;

	Player* player;

	Vector2 screenSize;

	Collision2D* collisionSystem;

	SDL_Texture* asteroidTexture;
	SDL_Texture* homingRocketTexture;
	SDL_Texture* rollingStoneTexture;

	double hazardSpawnDelay;
	double lastSpawnTime;

	double originalHazardSpawnDelay;

	int randSeed = 0;
};