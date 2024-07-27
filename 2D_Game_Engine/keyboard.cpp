#include "keyboard.h"
#include <iostream>
#include <map>
#include <SDL_events.h>
#include "commands.h"
#include <string>
#include "io/console.h"

///////////////////////////////////////////////////////////////
// Keyboard.cpp
// 
// This class is intended to be constructed once. It contains the code for parsing and handling keypress
// events. It also contains the map of data which connects virtual SDL keycodes to the commands which 
// should be executed upon the pressing of their respective keys. This class should NOT be used 
// outside of game.cpp, parseCFG.cpp, and any console commands. 
///////////////////////////////////////////////////////////////

//Stores keybindings; integer key is the SDL virtual keycode and string value is the associated command
//TODO: Allocate memory somewhere else. This is breaking some keys, seemingly
std::map<int, std::string>* keymap;

//Store what the key focus currently is. 
static game_keyfocus keyboardFocus;

Keyboard::Keyboard() {
	keymap = new std::map<int, std::string>();
}

Keyboard::~Keyboard() {}

bool Keyboard::keyboardEventConsole(int sym, SDL_EventType eventType) {
	//Try-catch doesn't work here because of terrible memory management stuff??
	//if (keymap->count(sym) == 1) {
		try {
			//std::cout << sym + " pressed! Command: " + keymap.at(sym) << std::endl;
			if (eventType == SDL_KEYDOWN)
			{
				if (sym == SDLK_BACKQUOTE) {
					setKeyboardFocus(gs_keyboard_game);
					Console::closeConsole();
				} else if (sym == SDLK_RETURN) {
					Console::newLine();
				} else if (sym == SDLK_BACKSPACE) {
					Console::backspace();
				}
				else if (sym == SDLK_LEFT) {
					Console::cursorLeft();
				}
				else if (sym == SDLK_RIGHT) {
					Console::cursorRight();
				}
				else {
					//If this is a keydown command, just run the bound command
					Console::writeChar(sym);
				}
			}
			else
			{
				//If this is a keyup command, check if we need to do anything
				
			}
			return true;
		}
		catch (std::out_of_range) {
			return false;
		}
	//}
	//else {
		//return false;
	//}
}

bool Keyboard::keyboardEventGame(int sym, SDL_EventType eventType) {
	//Try-catch doesn't work here because of terrible memory management stuff??
	if (keymap->count(sym) == 1) {
		try {
			//std::cout << sym + " pressed! Command: " + keymap.at(sym) << std::endl;
			if (eventType == SDL_KEYDOWN)
			{
				if (sym == SDLK_BACKQUOTE) {
					setKeyboardFocus(gs_keyboard_console);
					Console::openConsole();
				}
				else {
					//If this is a keydown command, just run the bound command
					Commands::runCommand(keymap->at(sym));
				}
			}
			else
			{
				//If this is a keyup command, check if we need to do anything
				Commands::runCommand(keymap->at(sym + 654));
			}
			return true;
		}
		catch (std::out_of_range) {
			// Printing this string seemingly destroys things sometimes? On special keys (shift, alt)
			// it breaks, and on unbound standard keys, it prints nonsense/garbage memory?
			//std::cout << "No keybinding for " + sym << std::endl;
			return false;
		}
	}
	else {
		// Printing this string seemingly destroys things sometimes? On special keys (shift, alt) it
		// breaks, and on unbound standard keys, it prints nonsense/garbage memory?
		//std::cout << "No keybinding for " + sym << std::endl;
		return false;
	}
}

/**
 * Handles a keyboard event, given the SDL keycode of the pressed key
 *
 * @param int sym, the SDL keycode
 * @param SDL_EventType eventType, the keypress type (up or down)
 */
bool Keyboard::keyboardEvent(int sym, SDL_EventType eventType)
{
	if (keyboardFocus == gs_keyboard_game) {
		return keyboardEventGame(sym, eventType);
	}
	else if (keyboardFocus == gs_keyboard_console) {
		return keyboardEventConsole(sym, eventType);
	}
	else if (keyboardFocus == gs_keyboard_menu) {
		//TODO
	}
	else {
		return false;
	}
}


/**
 * Binds a key to a command
 * 
 * @param int sym, virtual SDL keycode
 * @param std::string
 */
void Keyboard::bindKey(int sym, std::string keybindVal) 
{
	//If the key sym is currently bound to anything, get rid of that keybinding
	if (keymap->count(sym) == 1) {
		keymap->erase(sym);
	}
	//If the requested keybinding has a +, bind the key with a 654 higher value to the 
	//respective - command
	if (keybindVal[0] == '+') {
		keymap->insert(std::pair<int, std::string>(sym+654, '-'+keybindVal.substr(1, std::string::npos)));
	}

	keymap->insert(std::pair<int, std::string>(sym, keybindVal));
	printf("Just bound key!\n");
}

void Keyboard::setKeyboardFocus(game_keyfocus k) {
	keyboardFocus = k;
}