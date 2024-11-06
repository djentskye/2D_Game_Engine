#include "settings_menu.h"

void settings_menu::loadSettings(std::map<int, ui_element*>* elementQueue,
								 std::map<int, ui_element*>* nonselectableEementQueue, 
								 std::string trace) {
	//Clear the queue
	elementQueue->clear();
	nonselectableEementQueue->clear();

	//Add all relevant objects to the element queue
	UI_Text* t_settingsmenu = new UI_Text("Settings", 600, 50, 200, 80);
	nonselectableEementQueue->insert({ 0, t_settingsmenu });

	UI_Button* b_audio = new UI_Button("Audio", 100, 100, 200, 80);
	b_audio->setCommand("menu_settings_audio menu_settings " + trace);
	elementQueue->insert({ 0, b_audio });

	UI_Button* b_video = new UI_Button("Video", 100, 250, 200, 80);
	b_video->setCommand("menu_settings_video menu_settings " + trace);
	elementQueue->insert({ 1, b_video });

	UI_Button* b_controls = new UI_Button("Controls", 100, 400, 200, 80);
	b_controls->setCommand("menu_settings_controls menu_settings " + trace);
	elementQueue->insert({ 2, b_controls });

	UI_Button* b_back = new UI_Button("Back", 100, 550, 200, 80);
	b_back->setCommand(trace);
	elementQueue->insert({ 3, b_back });
}

void settings_menu::loadAudioSettings(std::map<int, ui_element*>* elementQueue,
									  std::map<int, ui_element*>* nonselectableEementQueue,
									  std::string trace) {
	//Clear the queue
	elementQueue->clear();
	nonselectableEementQueue->clear();

	//Add all relevant objects to the element queue
	UI_Text* t_settingsmenu = new UI_Text("Audio Settings", 600, 50, 200, 80);
	nonselectableEementQueue->insert({ 0, t_settingsmenu });

	UI_Button* b_back = new UI_Button("Back", 100, 550, 200, 80);
	b_back->setCommand(trace);
	elementQueue->insert({ 0, b_back });
}