#include <iostream>
#include <SDL.h>
#include "game.h"

#include <thread>

Game *g = nullptr;

void t_update()
{
	while (g->running())
	{
		g->update();
	}
}

int main(int argc, const char* argv[]) {
	g = new Game();

	g->init("djent", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, false);

	//We should use one thread for rendering and another thread for updating
	//Possibly use 
	
	while (g->running())
	{
		g->handleEvents();
		g->update();
		g->render();
	}

	g->clean();

	return 0;
}