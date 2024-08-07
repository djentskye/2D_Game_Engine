#include "bh_lava.h"

bh_lava::bh_lava() {
	w = 192;
	h = 128;
	texture = Texture::getTexture("assets/textures/meme1.png");
	physics_state = obj_dynamic;
	tick01 = Game::getTick();
	shooting = false;
	maxHealth = 40;
}

bh_lava::bh_lava(double xDest, double yDest) {
	x = xDest;
	y = yDest;
	w = 192;
	h = 128;
	texture = Texture::getTexture("assets/textures/meme1.png");
	physics_state = obj_dynamic;
	tick01 = Game::getTick();
	shooting = false;
	maxHealth = 40;
}

void bh_lava::shootProjectile() {
	Projectile* p = new Projectile(this, PROJ_MEME, -6, 0, 2);
}

/**
 * Akin to a death function. This is executed when health dips below zero
 */
void bh_lava::defeated() {
	Renderer::removeFromRenderQueue(this);
}

/**
 * Update function
 */
void bh_lava::update() {
	//Check if healthy
	if (health <= 0) {
		defeated();
	}

	//Movement

	//Attacks
	if (shooting && Game::getTick() > tick01) {
		shootProjectile();
		tick01 = Game::getTick() + 70;
	}
	
	//Updating misc states
}