#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "renderer.h"
#undef main

class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xPos, int yPos, int w, int h, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
	SDL_Window* getWindow();
	Renderer* getRenderer();
	void exit();
	Player* getPlayer();

private: 
	bool isRunning;
	SDL_Window *window;
	Renderer* renderer;
	Player* player;
};

