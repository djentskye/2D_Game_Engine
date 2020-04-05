#include "Game.h"
#include <SDL.h>
#include "sdl_image.h"
#include <iostream>
#include "player.h"
#include "objectmanager.h"

SDL_Texture* block;

Player* player;

ObjectManager om;

Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char* title, int xPos, int yPos, int w, int h, bool fullscreen)
{
	int flags = 0;
	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, w, h, flags);
		if (window)
		{
			std::cout << "Window created sucessfully" << std::endl;
		}

		renderer = new Renderer();
		renderer->init(window);

		isRunning = true;
	}
	else
	{
		std::cout << "Error initializing SDL" << std::endl;
		isRunning = false;
	}

	//Initialize the textures
	//SDL_Surface* tempSurface = IMG_Load("assets/textures/block.png");
	//block = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//SDL_FreeSurface(tempSurface);
	om.initObjects();

	player = new Player();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT: 
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	//if (SDL_GetTicks() % 10 == 0)
	//{
		//player->movePlayer(1, 1);
	//}
	om.updateObjects();
}

void Game::render()
{
	//SDL_RenderClear(renderer);

	//Render all objects

	//Sooner or later we want to outsource this to a render class that manages this
	//in a map, and that way we can just initialize to another map upon adding the
	//object, and loop through the map to render. 
	//SDL_RenderCopy(renderer, block, NULL, player->getDestination());
		//SDL_RenderCopy(renderer, om.);

	//SDL_RenderPresent;(renderer);

	renderer->render();
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	renderer->exit();
	SDL_Quit();
	std::cout << "Game has been cleared" << std::endl;
}

bool Game::running()
{
	return isRunning;
}

SDL_Window* Game::getWindow()
{
	return window;
}

Renderer* Game::getRenderer()
{
	return renderer;
}