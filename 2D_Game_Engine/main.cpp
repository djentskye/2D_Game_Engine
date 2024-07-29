#include <iostream>
#include <SDL.h>
#include "game.h"
#include "io/parseCFG.h"
#include "variables.h"
#include <thread>

Game *g = nullptr;

void t_update()
{
	//while (g->running())
	//{
		//g->handleEvents();
		g->update();
	//}
}

void t_render()
{
	//while (g->running())
	//{
		//if (Game::getTick() & 25 == 0) {
			g->render();
		//}
	//}
}

int main(int argc, const char* argv[]) {
	g = new Game();

	ParseCFG::parseCFG(g);

	g->init("djent", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2, 2, false);


	while (g->running())
	{
		g->handleEvents();
		//g->update();
		//g->render();
		// 
		//Start separate threads for rendering and updating
		std::thread updateThread(t_update);
		std::thread renderThread(t_render);
		updateThread.join();
		renderThread.join();
	}


	g->clean();

	return 0;
}