///////////////////////////////////////////////////////////////
// main.cpp
// 
// Main class for the game engine. This launches the game engine directly, with no 
// map editing functionality. It contains the int main() function and thread 
// functions. The main difference between main.cpp and game.cpp is their relative 
// scopes - main.cpp calls Game while handling high level execution and thread 
// operations, while game.cpp contains the functions called by main.cpp, which have
// more to do with the functionality of the engine itself. 
///////////////////////////////////////////////////////////////

#include <iostream>
#include <SDL.h>
#include "game.h"
#include "io/parseCFG.h"
#include "variables.h"
#include <thread>

Game *g = nullptr;

//Updating thread
void t_update()
{
	g->update();
}

//Rendering thread
void t_render()
{
	g->render();
}

//Unused events handling thread
void t_handleEvents() {
	g->handleEvents();
}

int main(int argc, const char* argv[]) {
	g = new Game();

	//Parse the config file, in the default path of cfg/config.cfg
	ParseCFG::parseCFG(g);

	//Initialize the game engine. This does a lot of important stuff!!
	g->init("djent", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2, 2, false);

	//Main game loop
	while (g->running())
	{
		g->handleEvents();

		//Start separate threads for rendering and updating
		std::thread updateThread(t_update);
		std::thread renderThread(t_render);

		//Join threads before the loop repeats. We want threads to process at the 
		//same time, but we want them all to stop before we start the next cycle. 
		updateThread.join();
		renderThread.join();
	}

	//Clean everything up
	g->clean();

	return 0;
}