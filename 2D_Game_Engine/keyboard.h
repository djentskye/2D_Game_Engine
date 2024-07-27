#ifndef KEYBOARD_H
#define KEYBOARD_H

#pragma once

#include <SDL_events.h>
#include <iostream>
#include "variables.h"

class Keyboard
{
public:
	Keyboard();
	~Keyboard();
	bool keyboardEvent(int sym, SDL_EventType eventType);
	void bindKey(int sym, std::string keybindVal);
	static void setKeyboardFocus(game_keyfocus k);

private:
	bool keyboardEventConsole(int sym, SDL_EventType eventType);
	bool keyboardEventGame(int sym, SDL_EventType eventType);

};

#endif