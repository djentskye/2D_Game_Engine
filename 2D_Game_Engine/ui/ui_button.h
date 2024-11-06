#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#pragma once

//#include <iostream>
#include "ui_element.h"
#include "../object.h"
#include "../texture.h"
#include "../io/fonts.h"
#include "../renderer.h"
#include "SDL.h"

typedef enum
{
	DEFAULT = 0
} BUTTON_STYLE;

class UI_Button : public ui_element
{
public:
	UI_Button(std::string txt, int x_dest, int y_dest, int width, int height);
	void setLocation(int x_dest, int y_dest);
	void setSize(int width, int height);
	void setStyle(BUTTON_STYLE requested_style);
	void setText(std::string txt);
	void setFont(std::string font_name);
	void setFontSize(int s);
	void setFontColor(SDL_Color c);
	void setTextLocation(int x, int y);
	void setTextCentered();
	void select();
	void deselect();
	void setCommand(std::string command);
	void onPress();
	void render();
	void update();
private:
	int text_x, text_y;
	std::string text;
	std::string font;
	SDL_Texture* text_texture;
	BUTTON_STYLE style;
	//int font_size;
	SDL_Color font_color;
	SDL_Rect* textRect;
	std::string on_press;
	int TEXT_WIDTH, TEXT_HEIGHT;
};

#endif