#include "object.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

//int x, y, w, h;
SDL_Texture* tex;
std::string name;

Object::Object()
{
}


Object::~Object()
{
}

SDL_Rect* Object::getDestination()
{
	SDL_Rect* dest = new SDL_Rect();
	dest->x = x;
	dest->y = y;
	dest->h = h;
	dest->w = w;
	return dest;
}

bool Object::setTexture(const char* path, SDL_Renderer *renderer)
{
	//TODO: Try/catch for bad texture paths
	SDL_Surface* tempSurface = IMG_Load(path);
	tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return true; //change this
}

//we're opting to return nothing (instead of returning a bool) and throwing an exception
//if we get an error. 
//void Object::renderObject(SDL_Renderer* renderer) //Do we have params??
//{
	//SDL_RenderCopy(renderer, block, NULL, player->getDestination());
	//SDL_RenderCopy(renderer, tex, NULL, getDestination());
//}

std::string Object::getName()
{
	return name;
}

int Object::getDepth()
{
	return d;
}

SDL_Texture* getTexture()
{
	return tex;
}