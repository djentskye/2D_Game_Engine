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
	void renderConsole();
	void render();
	SDL_Renderer* getRenderer();
	static int addToRenderQueue(Object* o);
	static int addToRenderQueue(Player* p);
	static void addToRenderQueue(int i, Object o);
	static void removeFromRenderQueue(Object* o);

private:
	//SDL_Renderer *renderer;
	//std::map<int, Object*> renderQueue;
	//std::map<int, Object*> consoleRenderQueue;
};

