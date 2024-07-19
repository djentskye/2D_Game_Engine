#include <iostream>
#include <fstream>
#include "parseCFG.h"
#include "../keyboard.h"
#include "SDL_keycode.h"
#include <ctype.h>

/**
 * Parses keybindings from the provided path
 */
void parseKeybindings(std::string filepath, Keyboard keyboard) {
	
}

/**
 * Parses keybindings from default path (cfg/keybindings.cfg) into the requested keyboard object
 */
void ParseCFG::parseKeybindings(Keyboard keyboard) {
	std::ifstream keybindingFile;
	keybindingFile.open("cfg/keybindings.cfg");

	std::string tempString;
	std::string key;
	std::string command;
	int cursor;
	bool bound;

	if (keybindingFile.is_open()) {
		while (getline(keybindingFile, tempString)) {
			if (tempString.substr(0, 5) == "bind ") {
				//Clear the storage of key and command values
				key = "";
				command = "";
				cursor = 5;
				bound = false;
				//starting at char index 5, get the key value
				while (tempString[cursor] != ' ') {
					//Append every character to the key value
					key += tempString[cursor];
					cursor++;
				}
				cursor++;
				//Next, do the same with the command
				while (tempString[cursor] != '\0') {
					command += tempString[cursor];
					cursor++;
				}
				//Remove quotes from around a command, if needed
				if (command.front() == '"' && command.back() == '"') {
					command.erase(command.length() - 1, 1);
					command.erase(0, 1);
				}
				for (int i = 0; i < key.length(); i++) {
					if (!isdigit(key[i])) {
						//This means the binding is not a number. We have to convert it! 
						
						//Convert individual keys. Since in SDL keycodes have the same value as their 
						//ascii counterparts, just use the value of the character! 
						if (key.length() == 1) {
							keyboard.bindKey(std::tolower(key[0]), command);
							bound = true;
							break;
						} 

						//Convert specific keys. Should be obvious based on name. 
						else if (key == "space" || key == "SPACE") {
							keyboard.bindKey(SDLK_SPACE, command);
							bound = true;
							break;
						} else if (key == "enter" || key == "ENTER") {
							keyboard.bindKey(SDLK_KP_ENTER, command);
							bound = true;
							break;
						}
						else if (key == "del" || key == "delete" || key == "DEL" || key == "DELETE") {
							keyboard.bindKey(SDLK_DELETE, command);
							bound = true;
							break;
						}
					}
				}

				//If the binding key was given as a number, bind the key. 
				if (bound == false) {
					//Bind the key to the required value
					keyboard.bindKey(std::stoi(key), command);
					bound = true;
				}
			}
		}
	}
	else {
		printf("Could not open cfg/keybindings.cfg");
	}

	keybindingFile.close();
}