#ifndef BH_LAVA_H
#define BH_LAVA_H

#pragma once

#include <iostream>
#include "SDL.h"
#include "../object.h"
#include <chrono>
#include "../texture.h"
#include "../variables.h"
#include "../game.h"
#include "../projectile.h"

class bh_lava: public Object
{
public:
	bh_lava();
	bh_lava(double x, double y);
	void init();
	void update();
private:
	void shootProjectile();
	void defeated();
	bool shooting;
	long long tick01;
	
};

#endif