#ifndef COMMANDS_H
#define COMMANDS_H

#pragma once

#include <SDL_events.h>
#include <iostream>
#include "game.h"


class Commands
{
public:
	Commands();
	~Commands();
	Commands(Game* g);
	static void runCommand(std::string str);

private: 
	static Game* game;
};

#endif