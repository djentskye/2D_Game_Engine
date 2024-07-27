#include "texture.h"
#include "renderer.h"

SDL_Renderer* renderer;

void Texture::init(Renderer* r) {
	renderer = r->getRenderer();
}

SDL_Texture* Texture::getTexture(const char* path) {
	//TODO: Try/catch for bad texture paths
	SDL_Surface* tempSurface = new SDL_Surface();
	tempSurface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}