#include "commands.h"
#include <iostream>
#include "game.h"
#include <string>
#include "gamestates.h"

Game* Commands::game;

Commands::Commands() {}

Commands::~Commands() {}

Commands::Commands(Game* g) {
	game = g;
}

/**
 * Runs the command specified by str
 * 
 * @param std::string str
 */
void Commands::runCommand(std::string str/*, game_leveltype gamemode*/) {
	if(str == "quit" || str == "exit") {
		game->exit();
		return;
	}
	if (str == "djent") {
		std::cout << "djent" << std::endl;
		return;
	}
	if (str == "+left") {
		//TODO: Pass gamemode to startMovingLeft....
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
	if (str.substr(0, 3) == "map") {
		std::string toLoad = str.substr(4, std::string::npos);
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
}