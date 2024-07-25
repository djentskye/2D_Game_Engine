#ifndef FONTS_H
#define FONTS_H

#pragma once

#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include <map>

class Fonts
{
public: 
	static void init(SDL_Renderer* rend);
	static TTF_Font* loadFont(std::string name, int size);
	static SDL_Texture* getRenderedText(std::string text, std::string font, int size, SDL_Color color);
private:
};

#endif