#ifndef COMMANDS_H
#define COMMANDS_H

#pragma once

#include <SDL_events.h>
#include <iostream>
#include "game.h"
#include "variables.h"


class Commands
{
public:
	Commands();
	~Commands();
	Commands(Game* g);
	static void runCommand(std::string str);

private: 
	static Game* game;
	static void runMenusCommand(std::string str);
};

#endif