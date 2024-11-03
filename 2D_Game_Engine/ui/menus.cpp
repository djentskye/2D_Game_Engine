///////////////////////////////////////////////////////////////
// ui/menus.cpp
// 
// 
///////////////////////////////////////////////////////////////

#include "menus.h"

std::map<int, ui_element*> elementQueue;
static ui_element* cursor_element;
static SDL_Texture* cursor_texture;
static SDL_Rect cursor_rect;
static bool cursor_anim; //false means shrinking, true means growing

void Menus::init() {
	//elementQueue = new std::map<int, ui_element*>();
	cursor_texture = Texture::getTexture("selection_box2.png");
}

void Menus::displayMainMenu() {
	//Add all relevant objects to the element queue
	Button* b = new Button("test", 100, 100, 200, 80);
	b->setCommand("exit");
	elementQueue.insert({0, b});

	cursor_element = elementQueue.at(0);
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
	if (cursor_anim && cursor_rect.x > cursor_element->getX() - 15) {
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
	}

	SDL_RenderCopy(Renderer::getRenderer(), cursor_texture, NULL, &cursor_rect);
}