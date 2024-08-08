///////////////////////////////////////////////////////////////
// texture.cpp
// 
// This class loads textures. It must be initialized in game.cpp. 
///////////////////////////////////////////////////////////////

#include "texture.h"
#include "renderer.h"

SDL_Renderer* renderer;

/**
 * Initializes the texture class
 */
void Texture::init(Renderer* r) {
	renderer = r->getRenderer();
}

/**
 * Returns an SDL_Texture* with the texture at the provided path
 */
SDL_Texture* Texture::getTexture(const char* path) {
	//TODO: Try/catch for bad texture paths
	SDL_Surface* tempSurface = new SDL_Surface();
	tempSurface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}