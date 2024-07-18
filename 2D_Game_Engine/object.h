#ifndef OBJECT_H
#define OBJECT_H

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Object
{
public:
	Object();
	~Object();
	SDL_Rect* getDestination();
	bool setTexture(const char* path, SDL_Renderer *renderer);
	bool setTexture(SDL_Texture* texture);
	bool setTextureFromObject(Object obj);
	std::string getName();
	int getDepth();
	SDL_Texture* getTexture();
	int getID();

private:
	//x coord, y coord, width, height, depth
	int x, y, w, h, d;
	SDL_Texture* tex;
	std::string name;
	int id;
	//static int nextID;
};

#endif