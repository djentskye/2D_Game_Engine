#include "projectile.h"
#include "texture.h"
#include "objectmanager.h"
#include "renderer.h"
#include "game.h"

Projectile::Projectile(Object* from) {
	shotBy = from;

	ObjectManager::addObject(this);

	rendererValue = Renderer::addToRenderQueue(this);
	destroyed = false;
}

Projectile::Projectile(Object* from, PROJ_TypeCode type, double x_vel, double y_vel, double dmg) {

	std::cout << Game::getTick() << std::endl;

	shotBy = from;
	projType = type;
	damage = dmg;

	if (type == PROJ_GREEN) {
		texture = Texture::getTexture("assets/textures/green_bullet.png");
		w = 20;
		h = 20;
	}
	SDL_Point originCenter = from->getCenter();

	x = (originCenter.x - w / 2);
	y = (originCenter.y - h / 2);

	velx = x_vel;
	vely = y_vel;

	physics_state = obj_proj;
	destroyed = false;
	dissappearOnHit = true;

	ObjectManager::addObject(this);

	rendererValue = Renderer::addToRenderQueue(this);

}

Projectile::~Projectile() {}

void Projectile::setDamage(double dmg) {
	damage = dmg;
}

/**
 * Deals damage upon collision. Returns false if the projectile disappears.
 */
bool Projectile::onCollision(Object* o) {
	//Don't deal damage to the entity that shot this projectile!
	if (o->getID() == shotBy->getID()) {
		return true;
	}
	o->addHealth(-damage);

	if (dissappearOnHit) {
		Renderer::removeFromRenderQueue(this);

		return false;
	}
	return true;
}

void Projectile::update() {

}