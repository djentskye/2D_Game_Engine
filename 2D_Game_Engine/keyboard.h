#ifndef KEYBOARD_H
#define KEYBOARD_H

#pragma once

#include <SDL_events.h>
#include <iostream>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();
	bool keyboardEvent(int sym);
	void bindKey(int sym, std::string keybindVal);
};

#endif