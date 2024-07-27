#include "renderer.h"
#include <iostream>
#include "player.h"
#include "io/console.h"

std::map<int, Object*> renderQueue;

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

/**
 * Initialize the renderer
 *
 * @param SDL_Window* window
 */
void Renderer::init(SDL_Window* window) 
{
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer)
	{
		//Clear the screen with black
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		std::cout << "Renderer has been created" << std::endl;
	}
}

/**
 * Destroy the renderer
 */
void Renderer::exit()
{
	SDL_DestroyRenderer(renderer);
}

void Renderer::renderConsole() {
	//Render the cursor
	SDL_Color cursorColor = Console::getCursorColor();
	if (SDL_GetTicks() % 10 < 5) {
		SDL_SetRenderDrawColor(renderer, cursorColor.r, cursorColor.g, cursorColor.b, 255);
	}
	else {
		SDL_SetRenderDrawColor(renderer, cursorColor.r, cursorColor.g, cursorColor.b, 0);
	}

	SDL_Rect* test = Console::getCursorObj()->getDestination();

	SDL_RenderDrawRect(renderer, Console::getCursorObj()->getDestination());

	//TODO: This is super clunky lol, in the future we should have pointers in this class.
	Object* backgroundObj = Console::getBackgroundObj();
	std::list<Object*> textObjMap = *Console::getTextObjMap();

	//Render the background
	SDL_RenderCopy(renderer, backgroundObj->getTexture(), NULL, backgroundObj->getDestination());

	//Render the text
	for (Object* element : textObjMap) {
		SDL_RenderCopy(renderer, element->getTexture(), NULL, element->getDestination());
	}
}

//TODO: [REND] Add a render sorter
//TODO: [REND] Multiple obj layers
/**
 * Render to the screen
 *
 * This basically processes all of our rendering. Render order should be adjusted
 * here, and all objects are rendered from the render queue. 
 */
void Renderer::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Literally render everything here
	//TODO: [REND] Implement a system for render order
	//TODO: [REND] Render background

	//TODO: [REND] Get an iterator to return things in order from lowest-highest depth
	for (std::pair<int, Object*> element : renderQueue) {
		//SDL_RenderCopy(renderer, element.second->getTexture(), NULL, element.second->getDestination());
		SDL_RenderCopyEx(renderer, element.second->getTexture(), NULL, element.second->getDestination(), element.second->getRotation(), NULL, element.second->getTextureFlip());
	}

	//Render the console if it's currently showing
	if (Console::consoleShowing()) {
		renderConsole();
	}

	SDL_RenderPresent(renderer);
}

//We want this to return a POINTER to the renderer; is this correct?
/**
 * Returns the renderer (?)
 */
SDL_Renderer* Renderer::getRenderer()
{
	return renderer;
}

/**
 * Adds an object to the render queue automatically
 *
 * This should be used for most rendering, though not if objects are intended to
 * be in a specific order
 *
 * @param Object o
 */
void Renderer::addToRenderQueue(Object* o)
{
	//Eventually we will need a method to change the depth by removing from render queue and re-adding
	renderQueue.insert(std::pair<int, Object*>(renderQueue.size()+1, o));
	//renderQueue.insert(std::pair<int, Object*>(renderQueue.() + 1, &o));
}

void Renderer::addToRenderQueue(Player* p)
{
	std::pair<int, Object*> tempPair = std::pair<int, Object*>(renderQueue.size() + 1, p);

	//Eventually we will need a method to change the depth by removing from render queue and re-adding
	renderQueue.insert(tempPair);

	printf("eeee");
}

/**
 * Adds an object to the render queue to a specific location
 *
 * @param int i
 * @param Object o
 */
void Renderer::addToRenderQueue(int i, Object o)
{
	//Eventually we will need a method to change the depth by removing from render queue and re-adding
	renderQueue.insert(std::pair<int, Object*>(i, &o)); //??? &
}