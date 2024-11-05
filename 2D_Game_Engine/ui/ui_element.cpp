#include "ui_element.h"

ui_element::ui_element() {
	rect = new SDL_Rect();
}

ui_element::~ui_element() {
	rect = new SDL_Rect();
}

/**
 * Returns the destination of an object
 */
SDL_Rect* ui_element::getDestination()
{
	rect->x = x;
	rect->y = y;
	rect->h = h;
	rect->w = w;
	return rect;
}

/**
 * Sets the destination to a set of doubles and integers.
 */
void ui_element::setDestination(double x, double y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

/**
 * Sets the destination to a set of doubles and integers.
 */
void ui_element::setDestination(double x, double y) {
	this->x = x;
	this->y = y;
}

int ui_element::getWidth() { return w; }

int ui_element::getHeight() { return h; }

double ui_element::getX() { return x; }

double ui_element::getY() { return y; }

void ui_element::setX(double x) { this->x = x; }

void ui_element::setY(double y) { this->y = y; }

void ui_element::setWidth(int width) { w = width; }

void ui_element::setHeight(int height) { h = height; }

void ui_element::setDepth(int d) { this->d = d; }

void ui_element::onPress() {}

/**
 * Sets the texture of an object to a preexisting texture
 *
 * @param SDL_Texture *texture
 */
bool ui_element::setTexture(SDL_Texture* newTexture) {
	texture = newTexture;
	return true;
}

SDL_RendererFlip ui_element::getTextureFlip() {
	return texture_flipped;
}

void ui_element::setTextureFlip(SDL_RendererFlip rf) {
	texture_flipped = rf;
}

/**
 * Renders the ui_element. This currently does nothing and shoud be overridden by 
 * child classes. The idea is that we use Renderer::getRenderer() to get access to 
 * the renderer object, and then the element itself can choose how it is rendered. 
 */
void ui_element::render() {
	//Renderer::getRenderer();
}

/**
 * Updates an object every tick. This is set as a simple movement function for now,
 * but can and should be overridden by child classes.
 */
void ui_element::update() {
	x += velx;
	y += vely;
}