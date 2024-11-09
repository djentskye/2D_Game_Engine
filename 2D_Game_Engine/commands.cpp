///////////////////////////////////////////////////////////////
// commands.cpp
// 
// This class runs and parses commands. Any new commands should be defined in 
// functions within this class. The runCommand() function is called upon any 
// command input, so be sure to reference something from in there. 
///////////////////////////////////////////////////////////////

#include "commands.h"
#include <iostream>
#include "game.h"
#include <string>
#include "gamestates.h"
#include "io/loadMap.h"
#include <algorithm>

Game* Commands::game;

Commands::Commands() {}

Commands::~Commands() {}

Commands::Commands(Game* g) {
	game = g;
}

/**
 * Runs the command specified by str. 
 * 
 * If-cases should only be a couple of lines long and call other functions. 
 * 
 * @param std::string str
 */
void Commands::runCommand(std::string str) {
	//Remove whitespace from the beginning of the command, if there is any
	while (str.length() > 0 && str[0] == ' ') {
		str = str.substr(1, std::string::npos);
	}

	if(str == "quit" || str == "exit") {
		Console::print("Exiting game");
		game->exit();
		return;
	}
	if (str == "djent") {
		Console::print("djent");
		return;
	}
	if (str == "+left") {
		game->getPlayer()->startMovingLeft();
		return;
	}
	if (str == "+right") {
		game->getPlayer()->startMovingRight();
		return;
	}
	if (str == "-left") {
		game->getPlayer()->stopMovingLeft();
		return;
	}
	if (str == "-right") {
		game->getPlayer()->stopMovingRight();
		return;
	}
	if (str == "+up") {
		game->getPlayer()->startMovingUp();
		return;
	}
	if (str == "+down") {
		game->getPlayer()->startMovingDown();
		return;
	}
	if (str == "-up") {
		game->getPlayer()->stopMovingUp();
		return;
	}
	if (str == "-down") {
		game->getPlayer()->stopMovingDown();
		return;
	}
	if (str == "+attack1") {
		game->getPlayer()->startAttacking();
		return;
	}
	if (str == "-attack1") {
		game->getPlayer()->stopAttacking();
		return;
	}
	if (str.substr(0, 4) == "map ") {
		std::string toLoad = str.substr(4, std::string::npos);

		if (!loadMap::load(toLoad)) {
			Console::print(toLoad + ".map not found");
		}
		else {
			Gamestates::setGamestate(gs_game);
		}

		return;
	}
	if (str.substr(0, 15) == "g_setGameState ") {
		if (str.substr(15, std::string::npos) == "gs_menu") {
			Gamestates::setGamestate(gs_menu);
			return;
		}
		if (str.substr(15, std::string::npos) == "gs_pausemenu") {
			Gamestates::setGamestate(gs_pausemenu);
			return;
		}
		if (str.substr(15, std::string::npos) == "gs_game") {
			Gamestates::setGamestate(gs_game);
			return;
		}
	}
	if (str.substr(0, 14) == "g_setGamemode ") {
		if (str.substr(14, std::string::npos) == "gs_bullethell") {
			Gamestates::setGamemode(gs_bullethell);
			return;
		}
		if (str.substr(14, std::string::npos) == "gs_overworld") {
			Gamestates::setGamemode(gs_overworld);
			return;
		}
	}
	if (str == "close_console") {
		Console::closeConsole();
		return;
	}
	if (str.substr(0, 5) == "menu_") {
		//We split up menu commands since they make this function much longer
		Commands::runMenusCommand(str);
	}

	Console::print("Command not found");
}

/**
 * Runs the menu command specified by str. This is a private function intended for 
 * use by the runCommand() function only. 
 *
 * @param std::string str
 */
void Commands::runMenusCommand(std::string str) {
	//Display the pause menu
	if (str.substr(0, 11) == "menu_pause " || str == "menu_pause") {
		Gamestates::setGamestate(gs_menu);

		//If we have a callback then store it
		if (str.length() > 11) {
			Menus::displayPauseMenu(str.substr(11, std::string::npos));

		}
		else {
			Menus::displayPauseMenu("");
		}

		if (Console::isOpen()) {
			Console::closeConsole();
		}

		return;
	}
	//Close the pause menu
	if (str == "menu_unpause") {
		Gamestates::setGamestate(gs_game);
		Menus::closePauseMenu();

		if (Console::isOpen()) {
			Console::closeConsole();
		}

		return;
	}
	//Display the main menu
	if (str.substr(0, 10) == "menu_main " || str == "menu_main") {
		Gamestates::setGamestate(gs_menu);

		//If we have a callback then store it
		if (str.length() > 10) {
			Menus::displayMainMenu(str.substr(10, std::string::npos));

		}
		else {
			Menus::displayMainMenu("");
		}

		if (Console::isOpen()) {
			Console::closeConsole();
		}

		return;
	}
	//Display the settings menu
	if (str.substr(0, 14) == "menu_settings " || str == "menu_settings") {
		Gamestates::setGamestate(gs_menu);

		//If we have a callback then store it
		if (str.length() > 14) {
			Menus::displaySettingsMenu(str.substr(14, std::string::npos));
		}
		else {
			Menus::displaySettingsMenu("");
		}

		if (Console::isOpen()) {
			Console::closeConsole();
		}

		return;
	}
	//Display the audio settings submenu
	if (str.substr(0, 20) == "menu_settings_audio " || str == "menu_settings_audio") {
		Gamestates::setGamestate(gs_menu);

		//If we have a callback then store it
		if (str.length() > 20) {
			Menus::displaySettingsAudioMenu(str.substr(20, std::string::npos));
		}
		else {
			Menus::displaySettingsAudioMenu("");
		}

		if (Console::isOpen()) {
			Console::closeConsole();
		}

		return;
	}
}