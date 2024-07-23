#include "Game.h"
#include <SDL.h>
#include "sdl_image.h"
#include <iostream>
#include "player.h"
#include "objectmanager.h"
#include "io/parseCFG.h"
#include "keyboard.h"
#include "commands.h"

SDL_Texture* block;

Keyboard keyboard;

ObjectManager om;

//Initialize a commands parser
Commands commands;

Game::Game()
{
}


Game::~Game()
{
}

/**
 * Initializes the game
 *
 * This function initializes SDL, creates the window, and performs general setup
 * for the engine before running anything. 
 *
 * @param const char* title
 * @param int xPos, yPos, w, h
 * @param bool fullscreen
 */
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

	//Create the command parser
	commands = Commands(this);

	//Load keybindings from CFG
	ParseCFG::parseKeybindings(keyboard);

	//Initialize the textures
	//SDL_Surface* tempSurface = IMG_Load("assets/textures/block.png");
	//block = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//SDL_FreeSurface(tempSurface);
	om.initObjects();

	player = new Player();
	player->init(renderer->getRenderer());

	renderer->addToRenderQueue(player);

	om.addObject(player);


	Object* floor = new Object();
	SDL_Rect* floorRect = new SDL_Rect;
	floorRect->x = -100;
	floorRect->w = 800;
	floorRect->y = 400;
	floorRect->h = 200;
	floor->setDestination(floorRect);
	floor->setPhysState(obj_static);
	floor->setTexture("assets/textures/purple.png", renderer->getRenderer());
	renderer->addToRenderQueue(floor);
	om.addObject(floor);
}

//TODO: This should be exported to a class of its own eventually
/**
 * Used for event handling
 */
void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	//Catch and handle keypress events
	case SDL_KEYDOWN:
		/*switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			//TODO: Create console, then add keybinding support for it
			isRunning = false;
			break;
		case SDLK_w:
			//Keybindings
			break;
		default:
			break;
		}*/
		keyboard.keyboardEvent(event.key.keysym.sym, SDL_KEYDOWN);
		
		break;
	//Catch other events
	case SDL_KEYUP:
		keyboard.keyboardEvent(event.key.keysym.sym, SDL_KEYUP);
		break;
	case SDL_QUIT: 
		isRunning = false;
		break;
	default:
		break;
	}
}

/**
 * Updates the game
 *
 * Currently updates objects only, will eventually update physics,
 * collision detection, and more
 */
void Game::update()
{
	//if (SDL_GetTicks() % 10 == 0)
	//{
		//player->movePlayer(1, 1);
	//}
	om.updateObjects();
	player->update();

	
}

/**
 * Renders the game
 */
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

/**
 * Destroys the window and quits SDL, closing the program
 */
void Game::clean()
{
	SDL_DestroyWindow(window);
	renderer->exit();
	SDL_Quit();
	std::cout << "Game has been cleared" << std::endl;
}

/**
 * Returns the running state of the game
 */
bool Game::running()
{
	return isRunning;
}

/**
 * Returns the window
 */
SDL_Window* Game::getWindow()
{
	return window;
}

/**
 * Returns the renderer
 */
Renderer* Game::getRenderer()
{
	return renderer;
}

/**
 * Exits the game
 */
void Game::exit() {
	isRunning = false;
}

Player* Game::getPlayer() {
	return player;
}