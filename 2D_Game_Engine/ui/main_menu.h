#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#pragma once

#include "ui_elements.h"

class main_menu
{
public:
	static void loadMainMenu(std::map<int, ui_element*>* elementQueue, 
		std::map<int, ui_element*>* nonselectableEementQueue, 
		std::string trace);
};

#endif