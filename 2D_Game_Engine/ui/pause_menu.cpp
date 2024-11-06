#include "pause_menu.h"

void pause_menu::loadPauseMenu(std::map<int, ui_element*>* elementQueue,
							   std::map<int, ui_element*>* nonselectableEementQueue, 
							   std::string trace) {
	//Clear the queue
	elementQueue->clear();
	nonselectableEementQueue->clear();

	//Add all relevant objects to the element queue
	UI_Button* b_start = new UI_Button("Resume", 100, 100, 200, 80);
	b_start->setCommand("g_setGameState gs_game");
	elementQueue->insert({ 0, b_start });

	UI_Button* b_settings = new UI_Button("Settings", 100, 250, 200, 80);
	b_settings->setCommand("menu_settings menu_pause " + trace);
	elementQueue->insert({ 1, b_settings });

	UI_Button* b_exit = new UI_Button("Exit", 100, 400, 200, 80);
	b_exit->setCommand("exit");
	elementQueue->insert({ 2, b_exit });
}