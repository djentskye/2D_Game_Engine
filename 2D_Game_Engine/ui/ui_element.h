#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "../variables.h"
#include <cmath>
//#include "../game.h"

class ui_element { 
public:
	ui_element();
	~ui_element();
	SDL_Rect* getDestination();
	void setDestination(double x, double y, int w, int h);
	void setDestination(double x, double y);
	double getX();
	double getY();
	int getWidth();
	int getHeight();
	void setX(double x);
	void setY(double y);
	void setWidth(int width);
	void setHeight(int height);
	void setDepth(int d);
	virtual void onPress();
	bool setTexture(SDL_Texture* texture);
	SDL_RendererFlip getTextureFlip();
	void setTextureFlip(SDL_RendererFlip rf);
	virtual void render();
	virtual void update();

protected:
	double x, y;
	int w, h, d;
	double velx, vely;
	SDL_Texture* texture;
	std::string name;
	SDL_RendererFlip texture_flipped;
	SDL_Rect* rect;
};

#endif