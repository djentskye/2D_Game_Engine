///////////////////////////////////////////////////////////////
// game.cpp
// 
// This is the game class, which acts as an interface between main classes and the 
// rest of the code. Most central functionality is performed in here, with main 
// classes focusing on only upper level/process management utilities. This allows
// us to easily instantiate different versions of the game engine easily. 
// 
// This class contains a lot of core variables and some essential functions. It 
// contains an initializing function, a rendering function, an update function, and 
// a handleEvents function. It also contains pointers to essential objects in the 
// game engine, window dimensions, and timing functionality. Most functions belong 
// outside of this class, unless they directly relate to the core of the game 
// engine. 
///////////////////////////////////////////////////////////////

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
#include "io/console.h"
#include "texture.h"
#include "projectile.h"
//#include "ui/menus.h"

SDL_Texture* block;

Keyboard keyboard;

ObjectManager om;

static Renderer* renderer;

//Initialize a commands parser
Commands commands;

static int WINDOW_WIDTH, WINDOW_HEIGHT;

static std::chrono::steady_clock GAME_TIMER;
static long long ticks;

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
void Game::init(const char* title, int xPos, int yPos, int w, int h, 
				bool fullscreen)
{
	int flags = 0;
	if (WINDOW_FULLSCREEN == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, WINDOW_WIDTH, WINDOW_HEIGHT, 
								  flags);
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

	if (TTF_Init() < 0) {
		std::cout << "Error initializing SDL TTF" << std::endl;
		isRunning = false;
	}

	SDL_RenderSetLogicalSize(renderer->getRenderer(), 1920, 1080);

	Texture::init(renderer);

	Projectile::init();

	Fonts::init(renderer->getRenderer());

	Gamestates::init();
	Gamestates::setGamestate(gs_menu);
	Gamestates::setGamemode(gs_overworld);

	//Create the command parser
	commands = Commands(this);

	//20, 6
	Console::init(20, 10, { 255, 255, 255, 255 }, "Inconsolata", {85, 10, 7, 160}, 
				  100);

	//Load keybindings from CFG
	ParseCFG::parseKeybindings(keyboard);

	//Initialize the textures
	om.initObjects();

	player = new Player();

	loadMap::initMapLoader(player, renderer, &om);

	//loadMap::load("test");
	//Gamestates::setGamestate(gs_menu);
	Menus::init();
	//menu = new Menus();
	//menu->displayMainMenu();
	Commands::runCommand("menu_main");

	ticks = 0;
}

//TODO: This should be exported to a class of its own eventually
/**
 * Used for event handling
 */
void Game::handleEvents()
{
	SDL_Event event;
	//SDL_PollEvent(&event);
	//switch (event.type)
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
	//case SDL_MOUSEBUTTONDOWN:

	//case SDL_MOUSEBUTTONUP:

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
	//if (SDL_GetTicks() % 4 == 0) {
	//if (GAME_TIMER.now().time_since_epoch().count() % 30 == 0) {
		ticks++;
		om.updateObjects();
		player->update();
		Console::update();
	//}
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

int Game::getWindowWidth() { return WINDOW_WIDTH; }

int Game::getWindowHeight() { return WINDOW_HEIGHT; }

long long Game::getTick() {
	return ticks;
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