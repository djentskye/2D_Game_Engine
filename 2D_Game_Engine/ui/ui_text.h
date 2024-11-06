#ifndef BUTTON_H
#define BUTTON_H

#pragma once

//#include <iostream>
#include "ui_element.h"
#include "../object.h"
#include "../texture.h"
#include "../io/fonts.h"
#include "../renderer.h"
#include "SDL.h"

class UI_Text : public ui_element
{
public:
	UI_Text(std::string txt, int x_dest, int y_dest, int width, int height);
	void setLocation(int x_dest, int y_dest);
	void setSize(int width, int height);
	void setText(std::string txt);
	void setFont(std::string font_name);
	void setFontSize(int s);
	void setFontColor(SDL_Color c);
	void setTextLocation(int x, int y);
	void setTextCentered();
	void render();
	void update();
private:
	int text_x, text_y;
	std::string text;
	std::string font;
	SDL_Texture* text_texture;
	//int font_size;
	SDL_Color font_color;
	SDL_Rect* textRect;
	std::string on_press;
	int TEXT_WIDTH, TEXT_HEIGHT;
};

#endif