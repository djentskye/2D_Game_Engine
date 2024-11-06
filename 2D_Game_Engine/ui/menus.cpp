///////////////////////////////////////////////////////////////
// ui/menus.cpp
// 
// 
///////////////////////////////////////////////////////////////

#include "menus.h"

std::map<int, ui_element*> elementQueue;
std::map<int, ui_element*> nonselectableElementQueue;
static ui_element* cursor_element;
static int cursor_element_int;
static SDL_Texture* cursor_texture;
static SDL_Rect cursor_rect;
static bool cursor_anim; //false means shrinking, true means growing
static std::string lastTrace;
static int animationCounter;

void Menus::init() {
	//elementQueue = new std::map<int, ui_element*>();
	cursor_texture = Texture::getTexture("assets/textures/selection_box2.png");
	lastTrace = "";
	//printf("");
	cursor_anim = true;
	animationCounter = 0;
}

void Menus::setCursorLocationByUIElement(ui_element* uiel) {
	cursor_rect.x = uiel->getX() - 30;
	cursor_rect.y = uiel->getY() - 20;
	cursor_rect.w = uiel->getWidth() + 60;
	cursor_rect.h = uiel->getHeight() + 40;

	animationCounter = 0;
}

void Menus::displayMainMenu(std::string trace) {
	lastTrace = trace;
	main_menu::loadMainMenu(&elementQueue, &nonselectableElementQueue, trace);

	cursor_element = elementQueue.at(0);
	cursor_element_int = 0;

	setCursorLocationByUIElement(cursor_element);
}

void Menus::displaySettingsMenu(std::string trace) {
	lastTrace = trace;
	settings_menu::loadSettings(&elementQueue, &nonselectableElementQueue, trace);

	cursor_element = elementQueue.at(0);
	cursor_element_int = 0;

	setCursorLocationByUIElement(cursor_element);
}

void Menus::displaySettingsAudioMenu(std::string trace) {
	lastTrace = trace;
	settings_menu::loadAudioSettings(&elementQueue, &nonselectableElementQueue, trace);

	cursor_element = elementQueue.at(0);
	cursor_element_int = 0;

	setCursorLocationByUIElement(cursor_element);
}

//Will be deprecated. lol
void Menus::closeMainMenu() {
	//Remove elements from top to bottom???
}

void Menus::displayPauseMenu(std::string trace) {
	lastTrace = trace;
	pause_menu::loadPauseMenu(&elementQueue, &nonselectableElementQueue, trace);

	cursor_element = elementQueue.at(0);
	cursor_element_int = 0;

	setCursorLocationByUIElement(cursor_element);
}

void Menus::closePauseMenu() {}

/**
 * Renders the active menu
 */
void Menus::renderActiveMenu() {
	for (std::pair<int, ui_element*> element : elementQueue) {
		element.second->render();
	}

	for (std::pair<int, ui_element*> element : nonselectableElementQueue) {
		element.second->render();
	}

	//Cycle through animation for the cursor!
	if (cursor_anim && cursor_rect.x > cursor_element->getX() - 30 && animationCounter == 7) {
		cursor_rect.x--;
		cursor_rect.y--;
		cursor_rect.w += 2;
		cursor_rect.h += 2;

		animationCounter = 0;
	} else if(animationCounter == 7) {
		cursor_anim = false;
		cursor_rect.x++;
		cursor_rect.y++;
		cursor_rect.w -= 2;
		cursor_rect.h -= 2;

		animationCounter = 0;
	}
	if (cursor_rect.x == cursor_element->getX() - 20) {
		cursor_anim = true;
	}
	animationCounter++;

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

std::string Menus::trace() {
	return lastTrace;
}