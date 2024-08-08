///////////////////////////////////////////////////////////////
// projectile.cpp
// 
// This class contains all information for projectiles. Each individual projectile 
// should be an instance of this class. Projectile types should be added to 
// projectile.h, as PROJ_TypeCode lets us keep track of differing projectiles and 
// give them properties appropriate to their type. 
///////////////////////////////////////////////////////////////

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

Projectile::Projectile(Object* from, PROJ_TypeCode type, double x_vel, 
					   double y_vel, double dmg) {
	shotBy = from;
	projType = type;
	damage = dmg;

	//Set the texture appropriately
	texture = setTexture(type);

	//Handle projectile sizing as needed
	if (type == PROJ_GREEN) {
		w = 32;
		h = 32;
	}
	else {
		w = 32;
		h = 32;
	}

	//Ensure that the projectile emits from the center of the projectile which shot
	//it. This should be expanded to outside functions in the future!
	SDL_Point originCenter = from->getCenter();
	x = (originCenter.x - w / 2);
	y = (originCenter.y - h / 2);

	velx = x_vel;
	vely = y_vel;

	physics_state = obj_proj;
	destroyed = false;
	dissappearOnHit = true;

	//Adds projectile to the object manager and render queue
	ObjectManager::addObject(this);
	rendererValue = Renderer::addToRenderQueue(this);
}

Projectile::~Projectile() {}

/**
 * Initialize the projectile map. This should be called once as a static function, 
 * while initializing the game engine
 */
void Projectile::init() {
	textureMap = new std::map<int, SDL_Texture*>();
}

/**
 * Sets the projectile's texture according to its PROJ_TypeCode. 
 */
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

/**
 * Sets the damage dealt by a projectile
 */
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

/**
 * Projectile update function
 */
void Projectile::update() {

}