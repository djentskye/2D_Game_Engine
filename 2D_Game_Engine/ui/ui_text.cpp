//#include "ui_element.h"
#include "ui_text.h"
#include "../commands.h"

UI_Text::UI_Text(std::string txt, int x_dest, int y_dest, int width, int height) {
	text = txt;
	x = x_dest;
	y = y_dest;
	w = width;
	h = height;
	font = "Inconsolata";
	//font_size = 16;
	font_color = {255, 255, 255, 150};
	//texture = Texture::getTexture("assets/textures/console_background.png");
	//rect = new SDL_Rect();
	textRect = new SDL_Rect();
	TEXT_WIDTH = 25;
	TEXT_HEIGHT = 40;
	setTextCentered();
	//rect->x = x;
	//rect->y = y;
	//rect->w = w;
	//rect->h = h;
	setText(txt);
	selectable = false;
}

void UI_Text::setLocation(int x_dest, int y_dest) {
	x = x_dest;
	y = y_dest;
}

void UI_Text::setSize(int width, int height) {
	w = width;
	h = height;
}

void UI_Text::setText(std::string txt) {
	text = txt;
	text_texture = Fonts::getRenderedText(txt, font, TEXT_WIDTH, font_color);

	textRect->x = text_x + x;
	textRect->y = text_y + y;
	textRect->w = txt.length() * TEXT_WIDTH;
	textRect->h = TEXT_HEIGHT;
	//TODO: Handle multiple lines of text on a button fluidly. This may have to go in 
	//		the fonts class. 
}

void UI_Text::setFont(std::string font_name) {
	font = font_name;
}

/**void Button::setFontSize(int s) {
	font_size = s;
}*/

void UI_Text::setFontColor(SDL_Color c) {
	font_color = c;
}

/**
 * Sets the location of text within the bounds of the button. 0, 0 will refer to the 
 * top left corner of the button. 
 * 
 * @param int x_dest
 * @param int y_dest
 */
void UI_Text::setTextLocation(int x_dest, int y_dest) {
	text_x = x_dest;
	text_y = y_dest;
}

void UI_Text::setTextCentered() {
	text_x = w / 2 - ((text.length() * TEXT_WIDTH)/2);
	text_y = h / 2 - ((/*Number of lines*/1 * TEXT_HEIGHT) / 2);
}

void UI_Text::render() {
	//Render the background texture
	//SDL_RenderCopy(Renderer::getRenderer(), texture, NULL, rect);

	//Render the text
	SDL_RenderCopy(Renderer::getRenderer(), text_texture, NULL, textRect);
}

void UI_Text::update() {
	//Play any animations or show selection here
}