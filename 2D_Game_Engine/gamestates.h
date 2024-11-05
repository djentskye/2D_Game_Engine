#pragma once

#include <iostream>
#include "variables.h"
#include "keyboard.h"

class Gamestates
{
public:
	static void init();
	static void setGamestate(game_state g);
	static game_state getGamestate();
	static void setGamemode(game_leveltype g);
	static game_leveltype getGamemode();

private:
};

