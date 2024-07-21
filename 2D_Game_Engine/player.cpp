#include "Player.h"
#include "object.h"
#include "variables.h"


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
 * Moves the player on x and y
 *
 * @param int amtx, amty
 */
void Player::movePlayer(int amtx, int amty)
{
	//TODO: Collision detection
	x += amtx;
	y += amty;
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

//???????
SDL_Rect* Player::getSource()
{
	return new SDL_Rect();
}

/**
 * Returns the destination of the player
 */
SDL_Rect* Player::getDestination()
{
	SDL_Rect* dest = new SDL_Rect();
	dest->x = x;
	dest->y = y;
	dest->h = h;
	dest->w = w;
	return dest;
}

/**
 * Returns the texture of the player
 */
SDL_Texture* Player::getTexture()
{
	return texture;
}

void Player::update()
{
	
}