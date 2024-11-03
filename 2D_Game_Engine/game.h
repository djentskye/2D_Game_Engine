#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "renderer.h"
#include "mouse.h"
#include <chrono>
#include "ui/menus.h"
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
	static Renderer* getRenderer();
	void exit();
	Player* getPlayer();
	void setWindowWidth(int w);
	void setWindowHeight(int h);
	void setWindowFullscreen(bool f);
	static int getWindowWidth();
	static int getWindowHeight();
	static long long getTick();

private: 
	bool isRunning;
	SDL_Window *window;
	Player* player;
	Menus* menu;

	//A few private variables that we want to keep track of!
	bool WINDOW_FULLSCREEN;
};

