#include "object.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

//int x, y, w, h;
SDL_Texture* tex;
std::string name;

//This is to correctly assign every object an ID value
static int nextID = 0;

Object::Object()
{
	id = nextID;
	nextID++;
}


Object::~Object()
{
}

/**
 * Returns the destination of an object
 */
SDL_Rect* Object::getDestination()
{
	SDL_Rect* dest = new SDL_Rect();
	dest->x = x;
	dest->y = y;
	dest->h = h;
	dest->w = w;
	return dest;
}

/**
 * Sets the texture of an object
 *
 * @param const char* path
 * @param SDL_Renderer *renderer
 */
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

/**
 * Returns the name of the object
 */
std::string Object::getName()
{
	return name;
}

/**
 * Returns the depth of the object
 */
int Object::getDepth()
{
	return d;
}

/**
 * Returns the texture of the object
 */
SDL_Texture* getTexture()
{
	return tex;
}