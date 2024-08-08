#pragma once
#include "object.h"
#include <iostream>
#include <map>
#include "player.h"
#include "io/console.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void init(SDL_Window* window);
	void exit();
	static void renderConsole();
	static void render();
	SDL_Renderer* getRenderer();
	static int addToRenderQueue(Object* o);
	static void addToRenderQueue(int i, Object o);
	static void removeFromRenderQueue(Object* o);

private:
	
};

