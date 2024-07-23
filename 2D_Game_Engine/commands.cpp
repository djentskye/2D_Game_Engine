#include "commands.h"
#include <iostream>
#include "game.h"

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
	}
	if (str == "+right") {
		game->getPlayer()->startMovingRight();
	}
	if (str == "-left") {
		game->getPlayer()->stopMovingLeft();
	}
	if (str == "-right") {
		game->getPlayer()->stopMovingRight();
	}
	if (str == "+up") {
		game->getPlayer()->startMovingUp();
	}
	if (str == "+down") {
		game->getPlayer()->startMovingDown();
	}
	if (str == "-up") {
		game->getPlayer()->stopMovingUp();
	}
	if (str == "-down") {
		game->getPlayer()->stopMovingDown();
	}
}