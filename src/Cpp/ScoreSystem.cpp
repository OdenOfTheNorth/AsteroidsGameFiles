#include "ScoreSystem.h"

ScoreSystem::ScoreSystem(RessourceManager* rM)
{
	ressourceManager = rM;
	LoadScore();
}

void ScoreSystem::UpdateScore(double time)
{
	score = (time - restartTime) * scoreMult;

}

void ScoreSystem::DisplayScoreScreen(SDL_Renderer* renderer)
{
	SDL_Color color = { 255,255,255 };
	SDL_Texture* texture = ressourceManager->GetText( "score: " + to_string(score) + " Highscore: " + to_string(highScore), 40, color, renderer);
	SDL_Rect rect;
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	rect = { 0,0,texW,texH };

	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void ScoreSystem::SaveScore()
{

	if (score < highScore) return;

	std::string scoreText = std::to_string(round(score));

	ofstream fileStream;
	fileStream.open(ressourceManager->scoreFilePath);

	fileStream.clear();

	fileStream << scoreText;
	fileStream.close();
}

void ScoreSystem::LoadScore()
{
	ifstream fileStream(ressourceManager->scoreFilePath);
	if (fileStream.is_open())
	{
		string output = "";
		getline(fileStream, output);
		highScore = stoi(output);

		cout << "HighScore = " << highScore << endl;
	}
	fileStream.close();

}

void ScoreSystem::ResetScore(double time)
{
	SaveScore();
	score = 0;
	restartTime = time;
}
