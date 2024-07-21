#include "object.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "variables.h"
#include <cmath>

//int x, y, w, h;
SDL_Texture* texture;
std::string name;
phys_state physics_state;

//This is to correctly assign every object an ID value
static int nextID = 0;

Object::Object()
{
	id = nextID;
	nextID++;
	destRect = new SDL_Rect();
}


Object::~Object()
{
}

/**
 * Returns the destination of an object
 */
SDL_Rect* Object::getDestination()
{
	destRect->x = x;
	destRect->y = y;
	destRect->h = h;
	destRect->w = w;
	return destRect;
}

void Object::setDestination(SDL_Rect* rect) {
	x = rect->x;
	y = rect->y;
	w = rect->w;
	h = rect->h;
}

/**
 * Returns the destination of an object
 */
SDL_Rect* Object::getBoundingBox()
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
 * TODO: Deprecate this function so it's less of a hassle to clean up memory later
 *
 * @param const char* path
 * @param SDL_Renderer *renderer
 */
bool Object::setTexture(const char* path, SDL_Renderer *renderer)
{
	//TODO: Try/catch for bad texture paths
	SDL_Surface* tempSurface = IMG_Load(path);
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return true; //change this
}

/**
 * Sets the texture of an object to a preexisting texture
 * 
 * @param SDL_Texture *texture
 */
bool Object::setTexture(SDL_Texture *texture) {
	texture = texture;
	return true;
}

/**
 * Sets the texture of an object given another object
 * 
 * @param Object obj
 */
bool Object::setTextureFromObject(Object obj) {
	texture = obj.getTexture();
	return true;
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
SDL_Texture* Object::getTexture()
{
	return texture;
}

int Object::getID()
{
	return id;
}

double Object::getVelocity() {
	return sqrt(pow(velx, 2) + pow(vely, 2));
}

double Object::getVelocityAngle() {
	return atan(vely/velx);
}

double Object::getXVelocity() {
	return velx;
}

double Object::getYVelocity() {
	return vely;
}

void Object::setVelocity(double x, double y) {
	velx = x;
	vely = y;
}

void Object::addToVelocity(double x, double y) {
	velx += x;
	vely += y;
}

double Object::getRotationVelocity() {
	return rotationVelocity;
}

void Object::setRotationVelocity(double vel) {
	rotationVelocity = vel;
}

void Object::addToRotationVelocity(double vel) {
	rotationVelocity =+ vel;
}

void Object::setPhysState(phys_state p) {
	physics_state = p;
}

phys_state Object::getPhysState() {
	return physics_state;
}

double Object::getRotation() {
	return rotation;
}

void Object::setRotation(double r) {
	rotation = r;
}

SDL_RendererFlip Object::getTextureFlip() {
	return texture_flipped;
}

void Object::setTextureFlip(SDL_RendererFlip rf) {
	texture_flipped = rf;
}

