#ifndef OBJECT_H
#define OBJECT_H

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "variables.h"

class Object
{
public:
	Object();
	~Object();
	SDL_Rect* getDestination();
	void setDestination(SDL_Rect* rect);
	bool setTexture(const char* path, SDL_Renderer *renderer);
	bool setTexture(SDL_Texture* texture);
	bool setTextureFromObject(Object obj);
	std::string getName();
	int getDepth();
	SDL_Texture* getTexture();
	int getID();
	double getXVelocity();
	double getYVelocity();
	void setVelocity(double x, double y);
	void addToVelocity(double x, double y);
	void setPhysState(phys_state p);
	phys_state getPhysState();

protected:
	//x coord, y coord, width, height, depth
	int x, y, w, h, d;
	double velx, vely;
	SDL_Texture* texture;
	std::string name;
	phys_state physics_state;

private:
	int id;
	//static int nextID;
};

#endif