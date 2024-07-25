#include "fonts.h"
#include <SDL_ttf.h>
#include <map>

//Inconsolata-VariableFont_wdth,wght

static std::map<std::pair<std::string, int>, TTF_Font*>* fontMap;
static SDL_Renderer* renderer;

/**
 * Initialize the font loader. 
 * 
 * @param SDL_Renderer* rend
 */
void Fonts::init(SDL_Renderer* rend) {
	renderer = rend;
	fontMap = new std::map<std::pair<std::string, int>, TTF_Font*>();
}

/**
 * Loads a font into memory and returns it. 
 * 
 * @param std::string name
 * @param int size
 */
TTF_Font* Fonts::loadFont(std::string name, int size) {
	std::string fontAddress = "fonts/" + name + ".ttf";

	//Load the font
	return TTF_OpenFont(fontAddress.c_str(), size);
}

/**
 * Returns a texture with the required text. Loads the font to memory per size, so try to use only one
 * or two sizes only. 
 * 
 * @param std::string text
 * @param std::string font
 * @param int size
 * @param SDL_Color color
 */
SDL_Texture* Fonts::getRenderedText(std::string text, std::string font, int size, SDL_Color color) {
	//Check if we already have this font loaded into memory!!
	for (std::pair<std::pair<std::string, int>, TTF_Font*> element : *fontMap) {
		if (element.first.first == font && element.first.second == size) {
			//Render the text!
			SDL_Surface* surface = TTF_RenderText_Solid(element.second, text.c_str(), color);

			return SDL_CreateTextureFromSurface(renderer, surface);
		}
	}

	//If we don't, load it. 
	//TODO: We can DEFINITELY make this more efficient. 
	TTF_Font* thisFont = loadFont(font, size);
	fontMap->emplace(std::make_pair(font, size), thisFont);

	//Render the text!
	SDL_Surface* surface = TTF_RenderText_Solid(thisFont, text.c_str(), color);

	return SDL_CreateTextureFromSurface(renderer, surface);
}