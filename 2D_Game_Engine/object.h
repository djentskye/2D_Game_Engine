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
	SDL_Rect* getBoundingBox();
	bool setTexture(const char* path, SDL_Renderer *renderer);
	bool setTexture(SDL_Texture* texture);
	bool setTextureFromObject(Object obj);
	std::string getName();
	int getDepth();
	SDL_Texture* getTexture();
	int getID();
	double getVelocity();
	double getVelocityAngle();
	double getXVelocity();
	double getYVelocity();
	void setVelocity(double x, double y);
	void addToVelocity(double x, double y);
	double getRotationVelocity();
	void setRotationVelocity(double vel);
	void addToRotationVelocity(double vel);
	void setPhysState(phys_state p);
	phys_state getPhysState();
	double getRotation();
	void setRotation(double r);
	SDL_RendererFlip getTextureFlip();
	void setTextureFlip(SDL_RendererFlip rf);
	SDL_Point getCenter();
	void setCenter(SDL_Point p);

protected:
	//x coord, y coord, width, height, depth
	int x, y, w, h, d;
	//Rotation value, rotation velocity (clockwise)
	double rotation, rotationVelocity;
	double velx, vely;
	SDL_Texture* texture;
	std::string name;
	phys_state physics_state;
	SDL_RendererFlip texture_flipped;
	SDL_Point center;
	SDL_Rect* destRect;

private:
	int id;
	//static int nextID;
};

#endif