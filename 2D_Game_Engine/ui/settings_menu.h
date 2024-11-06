#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#pragma once

#include "ui_elements.h"

class settings_menu
{
public:
	static void loadSettings(std::map<int, ui_element*>* elementQueue,
		std::map<int, ui_element*>* nonselectableEementQueue, 
		std::string trace);
	static void loadAudioSettings(std::map<int, ui_element*>* elementQueue,
		std::map<int, ui_element*>* nonselectableEementQueue,
		std::string trace);
};

#endif