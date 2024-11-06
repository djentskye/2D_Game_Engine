///////////////////////////////////////////////////////////////
// ui/menus.cpp
// 
// 
///////////////////////////////////////////////////////////////

#include "menus.h"

std::map<int, ui_element*> elementQueue;
static ui_element* cursor_element;
static int cursor_element_int;
static SDL_Texture* cursor_texture;
static SDL_Rect cursor_rect;
static bool cursor_anim; //false means shrinking, true means growing

void Menus::init() {
	//elementQueue = new std::map<int, ui_element*>();
	cursor_texture = Texture::getTexture("assets/textures/selection_box2.png");
	//printf("");
}

void Menus::setCursorLocationByUIElement(ui_element* uiel) {
	cursor_rect.x = uiel->getX() - 10;
	cursor_rect.y = uiel->getY() - 10;
	cursor_rect.w = uiel->getWidth() + 20;
	cursor_rect.h = uiel->getHeight() + 20;
}

void Menus::displayMainMenu() {
	//Add all relevant objects to the element queue
	Button* b_start = new Button("Start Game", 100, 100, 200, 80);
	b_start->setCommand("map test");
	elementQueue.insert({0, b_start });

	Button* b_settings = new Button("Settings", 100, 250, 200, 80);
	b_settings->setCommand("menu settings");
	elementQueue.insert({ 1, b_settings });

	Button* b_exit = new Button("Exit", 100, 400, 200, 80);
	b_exit->setCommand("exit");
	elementQueue.insert({ 2, b_exit });

	cursor_element = elementQueue.at(0);
	cursor_element_int = 0;

	//setCursorLocationByUIElement(elementQueue.at(0));
	setCursorLocationByUIElement(cursor_element);
}

void Menus::closeMainMenu() {
	//Remove elements from top to bottom???
}

void Menus::displayPauseMenu() {}

void Menus::closePauseMenu() {}

/**
 * Renders the active menu
 */
void Menus::renderActiveMenu() {
	for (std::pair<int, ui_element*> element : elementQueue) {
		element.second->render();
	}

	//Cycle through animation for the cursor!
	/*if (cursor_anim && cursor_rect.x > cursor_element->getX() - 15) {
		cursor_rect.x--;
		cursor_rect.y--;
		cursor_rect.w += 2;
		cursor_rect.h += 2;
	}
	else {
		cursor_anim == false;
		cursor_rect.x++;
		cursor_rect.y++;
		cursor_rect.w -= 2;
		cursor_rect.h -= 2;
	}

	if (cursor_rect.x == cursor_element->getX()) {
		cursor_anim = true;
	}*/

	SDL_RenderCopy(Renderer::getRenderer(), cursor_texture, NULL, &cursor_rect);
}

/**
 * Presses/uses the current menu item, if applicable
 */
void Menus::select() {
	cursor_element->onPress();
}

/**
 * Moves cursor left
 */
void Menus::cursorLeft() {
	//TODO
}

/**
 * Moves cursor right
 */
void Menus::cursorRight() {
	//TODO
}

/**
 * Moves cursor up
 */
void Menus::cursorUp() {
	//Ensure that we never move the cursor outside of the range of elements
	if (cursor_element_int > 0) {
		cursor_element_int--;
		cursor_element = elementQueue.at(cursor_element_int);
		setCursorLocationByUIElement(cursor_element);
	}
}

/**
 * Moves cursor down
 */
void Menus::cursorDown() {
	//Ensure that we never move the cursor outside of the range of elements
	if (cursor_element_int < elementQueue.size()-1) {
		cursor_element_int++;
		cursor_element = elementQueue.at(cursor_element_int);
		setCursorLocationByUIElement(cursor_element);
	}
}