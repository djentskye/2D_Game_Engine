#include "gamestates.h"

static game_state* gamestate;
static game_leveltype* gamemode;
static game_camerastate* camerastate;

void Gamestates::init() {
	gamestate = new game_state;
	gamemode = new game_leveltype;
	camerastate = new game_camerastate;
}

void Gamestates::setGamestate(game_state g) {
	*gamestate = g;
}

game_state* Gamestates::getGamestate() {
	return gamestate;
}

void Gamestates::setGamemode(game_leveltype g) {
	*gamemode = g;
}

game_leveltype* Gamestates::getGamemode() {
	return gamemode;
}