#include "commands.h"
#include <iostream>
#include "game.h"
#include <string>

Game* Commands::game;

Commands::Commands() {}

Commands::~Commands() {}

Commands::Commands(Game* g) {
	game = g;
}

void Commands::runCommand(std::string str) {
	if(str == "quit" || str == "exit") {
		game->exit();
		return;
	}
	if (str == "djent") {
		std::cout << "djent" << std::endl;
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
	if (str.substr(0, 3) == "map") {
		std::string toLoad = str.substr(4, std::string::npos);
		return;
	}
}