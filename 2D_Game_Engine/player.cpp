#include "Player.h"


int x, y, w, h;

Player::Player()
{
	x = 0;
	y = 0;
	w = 32;
	h = 32;
}

Player::~Player()
{
}

void Player::init(SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load("assets/textures/block.png");
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void Player::movePlayer(int amtx, int amty)
{
	x += amtx;
	y += amty;
}

void Player::movePlayerTo(int xVal, int yVal)
{
	x = xVal;
	y = yVal;
}

//???????
SDL_Rect* Player::getSource()
{
	return new SDL_Rect();
}

SDL_Rect* Player::getDestination()
{
	SDL_Rect* dest = new SDL_Rect();
	dest->x = x;
	dest->y = y;
	dest->h = h;
	dest->w = w;
	return dest;
}

SDL_Texture* Player::getTexture()
{
	return texture;
}

void Player::update()
{
	
}