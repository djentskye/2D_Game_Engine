#include "renderer.h"
#include <iostream>

std::map<int, Object*> renderQueue;

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::init(SDL_Window* window) 
{
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		std::cout << "Renderer has been created" << std::endl;
	}
}

void Renderer::exit()
{
	SDL_DestroyRenderer(renderer);
}

//TODO: Add a render sorter

void Renderer::render()
{
	SDL_RenderClear(renderer);

	//Literally render everything here
	//TODO: Implement a system for render order
	//TODO: Render background
	//TODO: Render objects
	//TODO: Render player

	for (std::pair<int, Object*> element : renderQueue) {
		SDL_RenderCopy(renderer, element.second->getTexture(), NULL, element.second->getDestination());
	}

	SDL_RenderPresent(renderer);
}

//We want this to return a POINTER to the renderer; is this correct?
SDL_Renderer* Renderer::getRenderer()
{
	return renderer;
}

void addToRenderQueue(Object o)
{
	//Eventually we will need a method to change the depth by removing from render queue and re-adding
	renderQueue.insert(std::pair<int, Object*>(renderQueue.size()+1, &o));
	//renderQueue.insert(std::pair<int, Object*>(renderQueue.() + 1, &o));
}

void addToRenderQueue(int i, Object o)
{
	//Eventually we will need a method to change the depth by removing from render queue and re-adding
	renderQueue.insert(std::pair<int, Object*>(i, &o)); //??? &
}