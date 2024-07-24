#ifndef LOADMAP_H
#define LOADMAP_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "../player.h"
#include "../renderer.h"
#include "../objectmanager.h"
#include "../object.h"

class loadMap
{
public:
	static void initMapLoader(Player* p, Renderer* rend, ObjectManager* objectManager);
	static bool load(std::string filepath);
	static Object* loadObject(std::string objData);

private:

};

#endif