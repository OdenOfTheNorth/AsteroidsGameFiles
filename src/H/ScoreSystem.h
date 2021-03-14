#pragma once
#include "RessourceManager.h"
#include <fstream>
#include <string>
#include <math.h>
#include <iostream>
using namespace std;

class ScoreSystem
{
	public:
		ScoreSystem(RessourceManager* rM);
		void UpdateScore(double time);
		void DisplayScoreScreen(SDL_Renderer* renderer);
		void SaveScore();
		void LoadScore();
		void ResetScore(double time);

		RessourceManager* ressourceManager;
	private:
		double score = 0;
		double restartTime = 0;
		double scoreMult = 13;
		double highScore;
};

