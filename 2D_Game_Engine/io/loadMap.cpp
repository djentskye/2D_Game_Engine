///////////////////////////////////////////////////////////////
// io/loadMap.cpp
// 
// This class does not need to be constructed, though it must be initialized. Maps 
// can be loaded to memory using just one filepath. There is not yet a cleaning 
// system to use after loading a map, but that reset function belongs here as well. 
///////////////////////////////////////////////////////////////

#include "loadMap.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../object.h"
#include "../player.h"
#include "../renderer.h"
#include "../objectmanager.h"
#include "../variables.h"
#include "../commands.h"
#include "../entities.h"
#include "../texture.h"

static Player* player;
static Renderer* renderer;
static ObjectManager* om;

/**
 * Initializes the map loader class by setting some necessary static variables. This MUST be run 
 * prior to loading a map. 
 *
 * @param Player* p
 * @param Renderer* rend
 * @param ObjectManager* objectManager
 */
void loadMap::initMapLoader(Player* p, Renderer* rend, ObjectManager* objectManager) {
	player = p;
	renderer = rend;
	om = objectManager;
}

/**
 * Returns an object specified by the string objData. Interprets an object's data within a map file 
 * and loads it into memory. objData should not have curly brackets around it. 
 *
 * @param std::string objData
 */
Object* loadMap::loadObject(std::string objData) {
	int counter = 0;
	std::string propertyString, valueString;
	Object* o = new Object;

	//Loop through each element of data
	while (counter < objData.length()-1) {
		propertyString.clear();
		valueString.clear();

		while (objData[counter] != '=') {
			propertyString.append(1, objData.c_str()[counter]);
			counter++;
		}
		counter++;
		while (objData[counter] != ';') {
			valueString.append(1, objData.c_str()[counter]);
			counter++;
		}
		counter++;

		//Handle the possible properties and values
		if (propertyString == "x") {
			o->setX(stoi(valueString));
		}
		else if (propertyString == "y") {
			o->setY(stoi(valueString));
		}
		else if (propertyString == "w") {
			o->setWidth(stoi(valueString));
		}
		else if (propertyString == "h") {
			o->setHeight(stoi(valueString));
		}
		else if (propertyString == "d") {
			o->setDepth(stoi(valueString));
		}
		else if (propertyString == "tex") {
			//o->setTexture(valueString, renderer->getRenderer());
			o->setTexture(Texture::getTexture(valueString.c_str()));
		}
		else if (propertyString == "name") {
			o->setName(valueString);
		}
		else if (propertyString == "phys_state") {
			//Our phys_state property needs to be stored as an integer lol
			o->setPhysState((phys_state)stoi(valueString));
		}
		else if (propertyString == "r") {
			o->setRotation(stod(valueString));
		}
		else if (propertyString == "type") {
			//Handles the type, if the object is an entity. When used, type should be the first
			//property defined in a .map file. 
			if (valueString == "bh_lava") {
				o = new bh_lava();
			}
		}
	}

	return o;
}

/**
 * Loads a map into memory from a given filepath
 * 
 * @param std::string filepath
 */
bool loadMap::load(std::string filepath) {

	std::ifstream mapFile;
	std::string fullMapString = "maps/" + filepath + ".map";
	mapFile.open(fullMapString);

	std::string tempString;

	if (mapFile.is_open()) {
		Commands::runCommand("close_console");
		Commands::runCommand("g_setGameState gs_game");
		while (getline(mapFile, tempString)) {
			if (tempString.substr(0, 12) == "playerSpawn=") {
				player->movePlayerTo(stoi(tempString.substr(12, 4)), stoi(tempString.substr(17, 4)));

				player->init(renderer->getRenderer());

				renderer->addToRenderQueue(player);

				om->addObject(player);
			}
			else if (tempString.substr(0, 4) == "obj=") {
				//Assume that the object data will be enclosed within brackets
				Object* o = loadMap::loadObject(tempString.substr(5, tempString.length() - 1));
				renderer->addToRenderQueue(o);
				om->addObject(o);
			}
			else if (tempString.substr(0, 2) == "//") {
				//Do nothing; this is a comment!
			}
			else if (tempString.substr(0, 14) == "g_setGamemode ") {
				Commands::runCommand(tempString);
			}
			else if (tempString.substr(0, 7) == "entity=") {
				Object* o = loadMap::loadObject(tempString.substr(8, tempString.length() - 2));
				renderer->addToRenderQueue(o);
				om->addObject(o);
			}
		}
	}
	else {
		std::cout << ("Could not open " + fullMapString) << std::endl;
		mapFile.close();
		return false;
	}

	mapFile.close();

	return true;
}

//TODO: Create a function that loads menus?? They can also be stored in map files
