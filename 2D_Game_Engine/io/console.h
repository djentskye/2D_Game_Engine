#ifndef CONSOLE_H
#define CONSOLE_H

#pragma once

#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include <map>
#include <list>
#include "../object.h"

class Console
{
public:
	Console();
	~Console();
	static void init(int text_h, int text_w, SDL_Color text_color, std::string text_font, 
		SDL_Color background_color, int background_opacity);
	static void openConsole();
	static void closeConsole();
	static void writeChar(int sym);
	static void newLine();
	static Object* getBackgroundObj();
	static std::list<Object*>* getTextObjMap();
	static void cursorLeft();
	static void cursorRight();
	static void cursorResetX();
	static void cursorDown();
	static Object* getCursorObj();
	static bool consoleShowing();
	static SDL_Color getCursorColor();
	static void backspace();
	static void setShift(bool b);
	static void update();

private:

};

#endif
