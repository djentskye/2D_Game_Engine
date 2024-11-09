///////////////////////////////////////////////////////////////
// Player.cpp
// 
// The palyer class. Though there's nothing static in this class, there should only
// be one instance of it at once. Most functions are handled internally for this 
// class. 
///////////////////////////////////////////////////////////////

#include "Player.h"
#include "object.h"
#include "variables.h"
#include <cmath>
#include <iostream>
#include "projectile.h"
#include "objectmanager.h"
#include "game.h"
#include "gamestates.h"

Player::Player()
{
	//Set some basic starting values
	x = 0;
	y = 0;
	w = 46;
	h = 46;
	name = "player";
	rotation = 0;
	velx = 0;
	vely = 0;
	playerMaxSpeed = 3;
	playerAccel = 1.2;
	frictionConst = 0.6;
	shooting = 0;
	tick01 = 0;

	//Set the physics state
	physics_state = obj_physics;

	//Set the default texture state to unflipped
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

/**
 * Returns the texture of the player
 */
SDL_Texture* Player::getTexture()
{
	return texture;
}

/**
 * Updates the player's movement. Private class. Should only be run from 
 * Player::update(). 
 */
void Player::updateMovement() {

	//We store the requested value 
	velx *= frictionConst;
	vely *= frictionConst;

	double newVelX = 0;
	double newVelY = 0;

	//Keep track of what our directional movement looks like
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
		xdest *= sqrt(2)/2;
		ydest *= sqrt(2)/2;
	}

	//Find the desired acceleration
	newVelX += velx + xdest * playerAccel;
	newVelY += vely + ydest * playerAccel;

	//Vector magnitude
	double desiredVecMagnitude = sqrt(pow(newVelX, 2.0) + pow(newVelY, 2));

	//Speed limiter
	if (desiredVecMagnitude > playerMaxSpeed) {
		//Make a unit vector, then multiply with max speed
		newVelX = playerMaxSpeed * (newVelX / desiredVecMagnitude);
		newVelY = playerMaxSpeed * (newVelY / desiredVecMagnitude);
	}

	velx = newVelX;
	vely = newVelY;
}

/**
 * Updates the player with anything that we might need to run from within the 
 * class. This is called whenever we are updating the scene as a whole. Add 
 * any functions here which should run from this class upon a tick update. 
 */
void Player::update()
{
	updateMovement();

	if (shooting && Gamestates::getGamemode() == gs_bullethell) {
		if (Game::getTick() > tick01) {
			shootProjectile();
			tick01 = Game::getTick() + 50;
		}
	}
}

void Player::shootProjectile() {
	Projectile* p = new Projectile(this, PROJ_GREEN, 3.5, 0, 2);
	tick01 = Game::getTick() + 50;
}

void Player::startAttacking() {
	shooting = true;
}

void Player::stopAttacking() {
	shooting = false;
	tick01 = 0;
}