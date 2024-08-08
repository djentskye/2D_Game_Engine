#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once

#include <iostream>
#include "SDL.h"
#include "texture.h"
#include "renderer.h"

class Texture
{
public:
	static void init(Renderer* r);
	static SDL_Texture* getTexture(const char* path);
};

#endif