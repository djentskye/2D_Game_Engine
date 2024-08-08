///////////////////////////////////////////////////////////////
// Gamestates.cpp
// 
// This class does not need to be constructed, though it must be initialized. It 
// keeps track of the game state, level type, and more settings that need to be 
// accessed at various points in the code. Use this if you need to figure out 
// what state the game engine is currently in!
///////////////////////////////////////////////////////////////

#include "gamestates.h"

static game_state* gamestate;
static game_leveltype* gamemode;
static game_camerastate* camerastate;

/**
 * Constructs the game state variables
 */
void Gamestates::init() {
	gamestate = new game_state;
	gamemode = new game_leveltype;
	camerastate = new game_camerastate;
}

/**
 * Sets the game state
 */
void Gamestates::setGamestate(game_state g) {
	*gamestate = g;
}

/**
 * Returns the game state
 */
game_state Gamestates::getGamestate() {
	return *gamestate;
}

/**
 * Sets the game mode
 */
void Gamestates::setGamemode(game_leveltype g) {
	*gamemode = g;
}

/**
 * Returns the game mode
 */
game_leveltype Gamestates::getGamemode() {
	return *gamemode;
}