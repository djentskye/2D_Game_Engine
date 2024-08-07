#include "projectile.h"
#include "texture.h"
#include "objectmanager.h"
#include "renderer.h"
#include "game.h"

static std::map<int, SDL_Texture*>* textureMap;

Projectile::Projectile(Object* from) {
	shotBy = from;

	ObjectManager::addObject(this);

	rendererValue = Renderer::addToRenderQueue(this);
	destroyed = false;
}

Projectile::Projectile(Object* from, PROJ_TypeCode type, double x_vel, double y_vel, double dmg) {
	shotBy = from;
	projType = type;
	damage = dmg;

	texture = setTexture(type);

	if (type == PROJ_GREEN) {
		w = 32;
		h = 32;
	}
	else {
		w = 32;
		h = 32;
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

void Projectile::init() {
	textureMap = new std::map<int, SDL_Texture*>();
}

SDL_Texture* Projectile::setTexture(PROJ_TypeCode projectileType) {

	try {
		return textureMap->at(projectileType);
	}
	catch (std::out_of_range) {
		switch (projectileType) {
		case PROJ_GREEN:
			textureMap->insert(std::pair<int, SDL_Texture*>(projectileType,
				Texture::getTexture("assets/textures/green_bullet.png")));
		case PROJ_ORANGE:
			textureMap->insert(std::pair<int, SDL_Texture*>(projectileType,
				Texture::getTexture("assets/textures/orange_bullet.png")));
		case PROJ_MEME:
			textureMap->insert(std::pair<int, SDL_Texture*>(projectileType,
				Texture::getTexture("assets/textures/meme2.png")));
		}
		return textureMap->at(projectileType);
	}
}


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