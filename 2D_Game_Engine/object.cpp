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

void Object::setDestination(double x, double y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void Object::setX(double x) { this->x = x; }

void Object::setY(double y) { this->y = y; }

void Object::setWidth(int width) { w = width; }

void Object::setHeight(int height) { h = height; }

void Object::setDepth(int d) {
	this->d = d;
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
bool Object::setTexture(const char* path, SDL_Renderer* renderer)
{
	//TODO: Try/catch for bad texture paths
	SDL_Surface* tempSurface = IMG_Load(path);
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return true; //change this
}

bool Object::setTexture(std::string path, SDL_Renderer* renderer)
{
	//TODO: Try/catch for bad texture paths
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
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
	if (velx == 0.0) {
		if (vely > 0) {
			return 180;
		}
		else {
			return 0;
		}
	}
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

void Object::setName(std::string newName) {
	name = newName;
}

void Object::setHealth(double h) {
	health = h;
}

void Object::setMaxHealth(double h) {
	maxHealth = h;
}

void Object::addHealth(double h) {
	health += h;
}

double Object::getHealth() {
	return health;
}

double Object::getMaxHealth() {
	return maxHealth;
}

void Object::shootProjectile() {
	
}