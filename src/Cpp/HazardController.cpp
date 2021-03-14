#include "HazardController.h"

HazardController::HazardController(double delayStart, Player* p, Vector2 screen, SDL_Renderer* rend, Collision2D* col, RessourceManager* rM)
{

	nextDifficultyIncreaseTime = difficultyIncreaseIntervals;
	hazardSpawnDelay = originalHazardSpawnDelay = delayStart;
	player = p;
	screenSize = screen;
	collisionSystem = col;

	asteroidTexture = rM->AsteroidTexture;
	homingRocketTexture = rM->RocketTexture;
	rollingStoneTexture = rM->RollingStoneTexture;

}

HazardController::~HazardController()
{
	//Destroy All Existing Asteroids
	for (int i = 0; i < asteroidPoolSize; i++)
	{
		if (asteroids[i] != NULL)
		{
			delete asteroids[i];
		}
	}

	//Destroy All Existing Homing Rockets
	for (int i = 0; i < homingRocketPoolSize; i++)
	{
		if (homingRockets[i] != NULL)
		{
			delete homingRockets[i];
		}
	}
}

void HazardController::Update(double deltaTime, double time)
{

	if (time > nextDifficultyIncreaseTime && hazardSpawnDelay - difficultySpawntimeDecrease > minSpawnDelay)
	{
		nextDifficultyIncreaseTime = time + difficultyIncreaseIntervals;
		hazardSpawnDelay -= difficultySpawntimeDecrease;
	}
	//Update Asteroids
	for (int i = 0; i < asteroidPoolSize; i++)
	{
		if (asteroids[i] != NULL)
		{
			if (asteroids[i]->isActive) 
			{
				asteroids[i]->Update(deltaTime);
			}
		}
	}

	for (int i = 0; i < rollingStonePoolSize; i++)
	{
		if (rollingStones[i] != NULL)
		{
			if (rollingStones[i]->isActive) rollingStones[i]->Update(deltaTime, time, screenSize);
		}
	}

	//Update Homing Rockets
	for (int i = 0; i < homingRocketPoolSize; i++)
	{
		if (homingRockets[i] != NULL)
		{
			if (homingRockets[i]->isActive)
			{
				homingRockets[i]->Update(player, deltaTime, time);
			}
		}
	}

	//Spawn Hazards
	if (time - lastSpawnTime > hazardSpawnDelay)
	{
		lastSpawnTime = time;
		spawnHazards();
	}
}

void HazardController::Render(SDL_Renderer * renderer)
{
	//Render Asteroids
	for (int i = 0; i < asteroidPoolSize; i++)
	{
		if (asteroids[i] != NULL)
		{
			if (asteroids[i]->isActive) asteroids[i]->Render(renderer);
		}
	}

	//Render Homing Rockets
	for (int i = 0; i < homingRocketPoolSize; i++)
	{
		if (homingRockets[i] != NULL)
		{
			if (homingRockets[i]->isActive) homingRockets[i]->Render(renderer);
		}
	}

	for (int i = 0; i < rollingStonePoolSize; i++)
	{
		if (rollingStones[i] != NULL)
		{
			if (rollingStones[i]->isActive) rollingStones[i]->Render(renderer);
		}
	}
}

//Spawn Hazards
void HazardController::spawnHazards()
{
	int hazardType = (GetRandom(0, 100) );

	if (hazardType < 20)
	{
		spawnRocket();
	}
	else if(hazardType < 90)
	{
		spawnAsteroid();
	}
	else
	{
		spawnRollingStones();
	}
}

//Spawn Asteroids
void HazardController::spawnAsteroid()
{
	int asteroidIndex = -1;

	for (int i = 0; i < asteroidPoolSize; i++)
	{
		if (asteroids[i] == nullptr)
		{
			asteroids[i] = new Asteroid(asteroidTexture, 
				std::vector<GameObject::CollisionLayers>{ GameObject::rockets, GameObject::player, GameObject::bullet }, GameObject::asteroids);

			//collisionSystem->AddCollider(asteroids[i], asteroids[i]->GetOnCollision);
			collisionSystem->AddCollider(asteroids[i]);
			asteroidIndex = i;

			break;
		}
		else if (!asteroids[i]->isActive)
		{
			asteroidIndex = i;
			break;
		}
	}

	if (asteroidIndex == -1) return;

	int astroidType = (GetRandom(0, 100));

	int size = GetRandom(50, 300);

	if (astroidType < 50)
	{
		double speed = 700 - (size * 2 - 200) + GetRandom(100, 200);

		int lives = size / 100 + 1;

		asteroids[asteroidIndex]->Init(player->position + Vector2(0, -1000), Vector2(0, speed), Vector2(), size, lives);
	}
	else
	{
		int speed = GetRandom(-50, 50);
		Vector2 pos;
		pos.x = (speed > 0) ? (0 - size) : screenSize.x;

		pos.y = GetRandom(0, lroundf(screenSize.y) / 2);

		double gravity = GetRandom(20, 25);

		asteroids[asteroidIndex]->Init(pos, Vector2(speed * 50, 0), Vector2(0,gravity), size, 1);
	}

}

//Spawn Homing Rockets
void HazardController::spawnRocket()
{
	int rocketIndex = -1;

	for (int i = 0; i < homingRocketPoolSize; i++)
	{
		if (homingRockets[i] == nullptr)
		{
			homingRockets[i] = new HomingRocket(homingRocketTexture,
				std::vector<GameObject::CollisionLayers>{ GameObject::asteroids, GameObject::player, GameObject::bullet }, GameObject::rockets);

			collisionSystem->AddCollider(homingRockets[i]);

			rocketIndex = i;

			break;
		}
		else if (!homingRockets[i]->isActive)
		{
			rocketIndex = i;
			break;
		}
	}

	if (rocketIndex == -1) return;

	int entrySide = GetRandom(0, 3);

	Vector2 startPos;

	//Enters from the left
	if (entrySide == 0)
	{
		startPos.x = 0;
		startPos.y = GetRandom(0, lroundf(screenSize.y) / 2);

	}
	//Enters from the top
	else if (entrySide == 1)
	{
		startPos.x = GetRandom(0, lroundf(screenSize.x));
		startPos.y = 0;

	}
	//Enters from the right
	else
	{
		startPos.x = screenSize.x;
		startPos.y = GetRandom(0,  lroundf(screenSize.y) / 2);

	}

	double speed = GetRandom(250, 650);

	homingRockets[rocketIndex]->Init(startPos, speed, player);

}

void HazardController::spawnRollingStones()
{
	int stoneIndex = -1;

	for (int i = 0; i < rollingStonePoolSize; i++)
	{
		if (rollingStones[i] == nullptr)
		{
			rollingStones[i] = new RollingStone(rollingStoneTexture,
				std::vector<GameObject::CollisionLayers>{ GameObject::player, GameObject::rockets }, GameObject::rollingStone);

			collisionSystem->AddCollider(rollingStones[i]);

			stoneIndex = i;

			break;
		}
		else if (!rollingStones[i]->isActive)
		{
			stoneIndex = i;
			break;
		}
	}

	if (stoneIndex == -1) return;

	int radius = GetRandom(25, 50);
	int speed = GetRandom(100, 150);
	int startSide = GetRandom(0, 100);
	cout << "Radius " << radius << endl;
	Vector2 startPos = Vector2(0, screenSize.y - radius * 2);
	Vector2 direction;

	if (startSide > 50)
	{
		startPos.x = -radius;
		direction = Vector2(1, 0);
	}
	else
	{
		startPos.x = screenSize.x + radius;
		direction = Vector2(-1, 0);
	}

	rollingStones[stoneIndex]->Init(startPos, speed, direction, radius);

}

int HazardController::GetRandom(int min, int max)
{
	randSeed++;
	randSeed *= 13;
	srand(time(NULL) + randSeed);

	return rand() % (max - min) + min;
}

void HazardController::ResetHazards()
{


	for (int i = 0; i < asteroidPoolSize; i++)
	{
		if (asteroids[i] != nullptr) 
		{
			asteroids[i]->isActive = false;
		}
	}

	for (int i = 0; i < homingRocketPoolSize; i++)
	{
		if (homingRockets[i] != nullptr)
		{
			homingRockets[i]->isActive = false;
		}
	}

	for (int i = 0; i < rollingStonePoolSize; i++)
	{
		if (rollingStones[i] != nullptr)
		{
			rollingStones[i]->isActive = false;
		}
	}

	hazardSpawnDelay = originalHazardSpawnDelay;
}
