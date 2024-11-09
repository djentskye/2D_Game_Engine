#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "object.h"
#include <chrono>

#undef main

class Player: public Object
{
public:
	Player();
	~Player();
	void init(SDL_Renderer* renderer);
	void movePlayer(int amtx, int amty);
	void movePlayerTo(int xVal, int yVal);
	void movePlayerAngle(double angle);
	void startMovingLeft();
	void stopMovingLeft();
	void startMovingRight();
	void stopMovingRight();
	void startMovingUp();
	void stopMovingUp();
	void startMovingDown();
	void stopMovingDown();
	SDL_Texture* getTexture();
	void update();
	void shootProjectile();
	void startAttacking();
	void stopAttacking();

private:
	//Playerspeed is the max speed the player can travel
	double playerMaxSpeed;
	double playerAccel;
	double movementAngle;
	bool moveLeft, moveRight, moveUp, moveDown;
	void updateMovement();
	bool shooting;
	long long tick01;
	//A friction constant that slows the player down when not moving
	double frictionConst;
};

#endif