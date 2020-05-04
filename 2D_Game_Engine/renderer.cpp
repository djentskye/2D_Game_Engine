#include "renderer.h"
#include <iostream>

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
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
	SDL_RenderClear(renderer);

	//Literally render everything here
	//TODO: [REND] Implement a system for render order
	//TODO: [REND] Render background
	//TODO: [REND] Render objects
	//TODO: [REND] Render player

	//TODO: [REND] Add objects to the render queue
	for (std::pair<int, Object*> element : renderQueue) {
		SDL_RenderCopy(renderer, element.second->getTexture(), NULL, element.second->getDestination());
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
void addToRenderQueue(Object o)
{
	//Eventually we will need a method to change the depth by removing from render queue and re-adding
	renderQueue.insert(std::pair<int, Object*>(renderQueue.size()+1, &o));
	//renderQueue.insert(std::pair<int, Object*>(renderQueue.() + 1, &o));
}

/**
 * Adds an object to the render queue to a specific location
 *
 * @param int i
 * @param Object o
 */
void addToRenderQueue(int i, Object o)
{
	//Eventually we will need a method to change the depth by removing from render queue and re-adding
	renderQueue.insert(std::pair<int, Object*>(i, &o)); //??? &
}