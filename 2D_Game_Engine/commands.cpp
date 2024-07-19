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
	}
	if (str == "djent") {
		std::cout << "djent" << std::endl;
	}
}