using namespace std;
#include <iostream>
#include "SDL.h"
#include "Game.h"



int main(int argc, char *argv[])
{
	Game* game = new Game("Asteroid",1000, 1000, 0);
		
	game->GameLoop();	

	return 0;
}