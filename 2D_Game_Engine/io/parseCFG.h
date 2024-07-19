#ifndef PARSECFG_H
#define PARSECFG_H

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "../keyboard.h"

class ParseCFG
{
public:
	ParseCFG();
	~ParseCFG();
	static void parseKeybindings(Keyboard keyboard);
	static void parseKeybindings(std::string filepath, Keyboard keyboard);

private:

};

#endif