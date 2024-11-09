//#include "ui_element.h"
#include "ui_button.h"
#include "../commands.h"

UI_Button::UI_Button(std::string txt, int x_dest, int y_dest, int width, int height) {
	text = txt;
	x = x_dest;
	y = y_dest;
	w = width;
	h = height;
	font = "Inconsolata";
	font_color = {255, 255, 255, 150};
	texture = Texture::getTexture("assets/textures/console_background.png");
	rect = new SDL_Rect();
	textRect = new SDL_Rect();
	TEXT_WIDTH = 25;
	TEXT_HEIGHT = 40;
	setTextCentered();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	setText(txt);
	selectable = true;
}

/**
 * Sets the location of the button
 * 
 * @param int x_dest
 * @param int y_dest
 */
void UI_Button::setLocation(int x_dest, int y_dest) {
	x = x_dest;
	y = y_dest;
}

/**
 * Sets the size of the button
 *
 * @param int width
 * @param int height
 */
void UI_Button::setSize(int width, int height) {
	w = width;
	h = height;
}

/**
 * Sets the style of the button, including texture and sizing options
 *
 * @param BUTTON_STYLE requested_style
 */
void UI_Button::setStyle(BUTTON_STYLE requested_style) {
	//Sets the style of the button to a pre-defined style
	//TODO: Implement this function fully
	style = requested_style;
}

/**
 * Sets the text to display on the button
 *
 * @param std::string txt
 */
void UI_Button::setText(std::string txt) {
	text = txt;
	text_texture = Fonts::getRenderedText(txt, font, TEXT_WIDTH, font_color);

	textRect->x = text_x + x;
	textRect->y = text_y + y;
	textRect->w = txt.length() * TEXT_WIDTH;
	textRect->h = TEXT_HEIGHT;
	//TODO: Handle multiple lines of text on a button fluidly. This may have to go in 
	//		the fonts class. 
}

/**
 * Sets the font for the button text
 * 
 * @param std::string font_name
 */
void UI_Button::setFont(std::string font_name) {
	font = font_name;
}

/**
 * Sets the color for the button text
 */
void UI_Button::setFontColor(SDL_Color c) {
	font_color = c;
}

/**
 * Sets the location of text within the bounds of the button. 0, 0 will refer to the 
 * top left corner of the button. 
 * 
 * @param int x_dest
 * @param int y_dest
 */
void UI_Button::setTextLocation(int x_dest, int y_dest) {
	text_x = x_dest;
	text_y = y_dest;
}

/**
 * Sets text to be centered on the button. 
 */
void UI_Button::setTextCentered() {
	text_x = w / 2 - ((text.length() * TEXT_WIDTH)/2);
	text_y = h / 2 - ((/*Number of lines*/1 * TEXT_HEIGHT) / 2);
}

void UI_Button::select() {}

void UI_Button::deselect() {}

/**
 * Set the command that should be run upon pressing the button (on_press)
 * 
 * @param std::string command
 */
void UI_Button::setCommand(std::string command) {
	on_press = command;
}

/**
 * Runs the button's on_press command
 */
void UI_Button::onPress() {
	Commands::runCommand(on_press);
}

/**
 * Renders the button
 */
void UI_Button::render() {
	//Render the background texture
	SDL_RenderCopy(Renderer::getRenderer(), texture, NULL, rect);

	//Render the text
	SDL_RenderCopy(Renderer::getRenderer(), text_texture, NULL, textRect);
}

/**
 * Updates the button
 */
void UI_Button::update() {
	//Play any animations or show selection here
}