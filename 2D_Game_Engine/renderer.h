#pragma once
#include "object.h"
#include <iostream>
#include <map>
#include "player.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void init(SDL_Window* window);
	void exit();
	void render();
	SDL_Renderer* getRenderer();
	void addToRenderQueue(Object* o);
	void addToRenderQueue(Player* p);
	void addToRenderQueue(int i, Object o);

private:
	SDL_Renderer *renderer;
	std::map<int, Object*> renderQueue;
};

