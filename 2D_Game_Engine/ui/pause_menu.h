#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#pragma once

#include "ui_elements.h"

class pause_menu
{
public:
	static void loadPauseMenu(std::map<int, ui_element*>* elementQueue, 
		std::map<int, ui_element*>* nonselectableEementQueue, 
		std::string trace);
};

#endif