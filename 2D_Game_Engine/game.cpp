#include "Game.h"
#include <SDL.h>
#include "sdl_image.h"
#include <iostream>
#include "player.h"
#include "objectmanager.h"
#include "io/parseCFG.h"
#include "keyboard.h"
#include "commands.h"
#include "io/loadMap.h"
#include "gamestates.h"
#include "io/fonts.h"

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
	if (WINDOW_FULLSCREEN == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, WINDOW_WIDTH, WINDOW_HEIGHT, flags);
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

	Fonts::init(renderer->getRenderer());

	Gamestates::init();
	Gamestates::setGamestate(gs_menu);
	Gamestates::setGamemode(gs_overworld);

	//Create the command parser
	commands = Commands(this);

	//Load keybindings from CFG
	ParseCFG::parseKeybindings(keyboard);

	//Initialize the textures
	om.initObjects();

	player = new Player();

	loadMap::initMapLoader(player, renderer, &om);

	loadMap::load("test");
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
	om.updateObjects();
	player->update();
}

/**
 * Renders the game
 */
void Game::render()
{
	//Render all objects
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

/**
 * Returns the player object pointer
 */
Player* Game::getPlayer() {
	return player;
}

void Game::setWindowWidth(int w) {
	WINDOW_WIDTH = w;
}

void Game::setWindowHeight(int h) {
	WINDOW_HEIGHT = h;
}

void Game::setWindowFullscreen(bool f) {
	WINDOW_FULLSCREEN = f;
}

/*
void Game::setGamestate(game_state g) {
	gamestate = g;
}

game_state Game::getGamestate() {
	return gamestate;
}

void Game::setGamemode(game_leveltype g) {
	gamemode = g;
}

game_leveltype Game::getGamemode() {
	return gamemode;
}
*/