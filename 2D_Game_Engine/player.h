#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "object.h"
#undef main

class Player: public Object //TODO: Make sure player works correctly as an object
{
public:
	Player();
	~Player();
	void init(SDL_Renderer* renderer);
	void movePlayer(int amtx, int amty);
	void movePlayerTo(int xVal, int yVal);
	SDL_Rect* getSource();
	SDL_Rect* getDestination();
	SDL_Texture* getTexture();
	void update();

private:
	//int x, y, w, h, d;
	//SDL_Texture* texture;
};

#endif