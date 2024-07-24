#include "Player.h"
#include "object.h"
#include "variables.h"
#include <cmath>
#include <iostream>


//int x, y, w, h;

Player::Player()
{
	x = 0;
	y = 0;
	w = 32;
	h = 32;
	rotation = 0;
	velx = 0;
	vely = 0;
	playerMaxSpeed = 0.1;
	playerAccel = 0.4;

	//Set the physics state
	physics_state = obj_physics;

	texture_flipped = SDL_FLIP_NONE;
}

Player::~Player()
{
}

/**
 * Initializes the player
 *
 * Currently uses stock assets, this should be configurable in the future
 *
 * @param SDL_Renderer* renderer
 */
void Player::init(SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load("assets/textures/block.png");
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

/**
 * Adds velocity to the character
 *
 * @param int amtx, amty
 */
void Player::movePlayer(int amtx, int amty)
{
	velx += amtx;
	vely += amty;
}

/**
 * Moves the player to a specific point
 *
 * @param int xVal, yVal
 */
void Player::movePlayerTo(int xVal, int yVal)
{
	//TODO: Location check
	x = xVal;
	y = yVal;
}

//TODO: Implement
void Player::movePlayerAngle(double angle) {
	//Start moving the character in the requested angle

}

void Player::startMovingLeft() {
	moveLeft = true;
}

void Player::stopMovingLeft() {
	moveLeft = false;
}

void Player::startMovingRight() {
	moveRight = true;
}

void Player::stopMovingRight() {
	moveRight = false;
}

void Player::startMovingUp() {
	moveUp = true;
}

void Player::stopMovingUp() {
	moveUp = false;
}

void Player::startMovingDown() {
	moveDown = true;
}

void Player::stopMovingDown() {
	moveDown = false;
}

//???????
SDL_Rect* Player::getSource()
{
	return new SDL_Rect();
}

/**
 * Returns the destination of the player
 */
/*SDL_Rect* Player::getDestination()
{
	SDL_Rect* dest = new SDL_Rect();
	dest->x = x;
	dest->y = y;
	dest->h = h;
	dest->w = w;
	return dest;
}*/

/**
 * Returns the texture of the player
 */
SDL_Texture* Player::getTexture()
{
	return texture;
}

void Player::updateMovement() {
	//We store the requested value 
	double newVelX = velx;
	double newVelY = vely;

	double xdest = 0;
	double ydest = 0;

	//Figure out what our direction is going to be
	if (moveLeft) {
		xdest--;
	}
	if (moveRight) {
		xdest++;
	}
	if (moveUp) {
		ydest--;
	}
	if (moveDown) {
		ydest++;
	}

	//If we are moving on both axes, multiply both by sqrt of 2
	if (abs(xdest) + abs(ydest) == 2) {
		xdest *= sqrt(2);
		ydest *= sqrt(2);
	}

	xdest += xdest * playerMaxSpeed;
	ydest += ydest * playerMaxSpeed;

	newVelX = xdest + playerAccel * (velx);
	newVelY = ydest + playerAccel * (vely);

	velx = newVelX;
	vely = newVelY;

	double vel = this->getVelocity();

	std::cout << "vel: ";
	std::cout << vel << std::endl;

	/*
	//If we are already at max speed while going right, we cannot increase our right velocity
	if (sqrt(abs(vely) + velx) >= playerSpeed) {
		//If we want to move left, start changing the velocity to go left
		if (moveLeft == true) {
			newVelX -= playerSpeed * playerAccel;
		} else if ()
	}


	else {
		velx -= -playerSpeed * playerAccel;
	}
	if (moveRight == true) {
		velx += playerSpeed * playerAccel;
	}
	else {
		velx -= playerSpeed * playerAccel;
	}
	if (moveUp == true) {
		vely += -playerSpeed * playerAccel;
	}
	else {
		vely -= -playerSpeed * playerAccel;
	}
	if (moveDown == true) {
		vely += playerSpeed * playerAccel;
	}
	else {
		vely -= playerSpeed * playerAccel;
	}
	/*





	/*double newXComponent = 0;
	double newYComponent = 0;
	double newMagnitude = 0;
	if (moveLeft == true && moveRight == true) {
		//No horizontal movement
	}
	else {
		//Apply horizontal angles
		if (moveLeft) {
			newXComponent = -1;
			newMagnitude++;
		}
		if (moveRight) {
			newXComponent = 1;
			newMagnitude++;
		}
	}
	if (moveUp == true && moveDown == true) {
		//No vertical movement
	}
	else {
		//Apply vertical angles
		if (moveUp) {
			newYComponent = -1;
			newMagnitude++;
		}
		if (moveDown) {
			newYComponent = 1;
			newMagnitude++;
		}
	}

	//Get some calculations out of the way
	double toAddX = newXComponent * playerAccel;
	double toAddY = newYComponent * playerAccel;
	double valueUntilSpeedLimit = playerSpeed - this->getVelocity();

	//Apply the change to velocity
	if (newMagnitude == 1) {
		//This only happens if the user is trying to go in one direction
		//If we are not going to reach the player's speed limit, just add our values to the vel
		if (valueUntilSpeedLimit > toAddX && valueUntilSpeedLimit > toAddY) {
			velx += toAddX;
			vely += toAddY;
		}
		else {
			velx += newXComponent * valueUntilSpeedLimit;
			vely += newYComponent * valueUntilSpeedLimit;
		}
	}
	else if (newMagnitude == 2) {
		toAddX = toAddX * sqrt(2);
		toAddY = toAddY * sqrt(2);
		//This happens if the user is trying to go in two directions
		//If we are not going to reach the player's speed limit, just add our values to the vel
		if (valueUntilSpeedLimit > toAddX && valueUntilSpeedLimit > toAddY) {
			velx += toAddX;
			vely += toAddY;
		}
		else {
			velx += newXComponent * valueUntilSpeedLimit;
			vely += newYComponent * valueUntilSpeedLimit;
		}
	}
	*/
}

void Player::update()
{
	updateMovement();
}