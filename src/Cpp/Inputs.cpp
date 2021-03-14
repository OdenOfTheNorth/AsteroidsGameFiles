#include "Inputs.h"


Inputs::Inputs()
{
}

Inputs::~Inputs()
{
}

void Inputs::UpdateInputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_KEYDOWN:
			ChangeKeyState(event, true);
			break;
		case SDL_QUIT:
			quitPressed = true;		
			cout << "Quit" << endl;
			break;
		case SDL_KEYUP: 
			ChangeKeyState(event, false);
		default:
			break;
		}
	}	
}

void Inputs::ChangeKeyState(SDL_Event event, bool state)
{

	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		wDown = state;
		//cout << "w Pressed, " << state << endl;
		break;
	case SDLK_s:
		sDown = state;
		break;
	case SDLK_a:
		aDown = state;
		break;
	case SDLK_d:
		dDown = state;
		break;
	case SDLK_ESCAPE:
		quitPressed = true;
		break;
	case SDLK_k:
		kDown = state;
		break;
	case SDLK_r:
		rDown = state;
		break;
	default:
		break;
	}
}