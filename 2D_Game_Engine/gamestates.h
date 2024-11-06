#pragma once

#include <iostream>
#include "variables.h"
//#include "keyboard.h"

class Gamestates
{
public:
	static void init();
	static void setGamestate(game_state g);
	static game_state getGamestate();
	static void setGamemode(game_leveltype g);
	static game_leveltype getGamemode();
	static game_state returnToPriorGamestate();
	static game_keyfocus gameStateToGameKeyfocus(game_state gs);
	static game_state getPriorGamestate();

private:
};

