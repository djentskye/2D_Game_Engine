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
	void setDestination(double x, double y, int w, int h);
	void setDestination(double x, double y);
	void setX(double x);
	void setY(double y);
	double getX();
	double getY();
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);
	void setDepth(int d);
	SDL_Rect* getBoundingBox();
	[[deprecated]] bool setTexture(const char* path, SDL_Renderer* renderer); 
	[[deprecated]] bool setTexture(std::string path, SDL_Renderer* renderer);
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
	void setName(std::string newName);
	void setHealth(double h);
	void setMaxHealth(double h);
	void addHealth(double h);
	double getHealth();
	double getMaxHealth();
	void shootProjectile();
	virtual void update();
	bool isEntity();

protected:
	//x coord, y coord, width, height, depth
	double x, y;
	int w, h, d;
	//Rotation value, rotation velocity (clockwise)
	double rotation, rotationVelocity;
	double velx, vely;
	double health;
	double maxHealth;
	SDL_Texture* texture;
	std::string name;
	phys_state physics_state;
	SDL_RendererFlip texture_flipped;
	SDL_Point center;
	SDL_Rect* destRect;
	bool entity;

private:
	int id;
};

#endif