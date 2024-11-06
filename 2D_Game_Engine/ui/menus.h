#ifndef MENUS_H
#define MENUS_H

#pragma once

#include <cmath>
#include <iostream>
#include "../object.h"
#include "ui_element.h"
#include "../variables.h"
#include "../objectmanager.h"
#include "../gamestates.h"
#include "ui_elements.h"
#include "../texture.h"
#include "main_menu.h"
#include "settings_menu.h"
#include "pause_menu.h"

class Menus
{
public:
	static void init();
	static void displayMainMenu(std::string trace);
	static void displaySettingsMenu(std::string trace);
	static void displaySettingsAudioMenu(std::string trace);
	static void closeMainMenu();
	static void displayPauseMenu(std::string trace);
	static void closePauseMenu();
	static void renderActiveMenu();
	static void select();
	static void cursorLeft();
	static void cursorRight();
	static void cursorUp();
	static void cursorDown();
	static std::string trace();

private:
	static void setCursorLocationByUIElement(ui_element* uiel);
	//References the currently selected element in the menu
	//int cursor_opacity;
	//double cursor_x, cursor_y, cursor_w, cursor_h;
};

#endif