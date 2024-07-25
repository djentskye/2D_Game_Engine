#include "projectile.h"

Projectile::Projectile(Object* from) {
	shotBy = from;
}

Projectile::~Projectile() {}

/**
 * Deals damage upon collision
 */
void Projectile::onCollision(Object* o) {
	//Don't deal damage to the entity that shot this projectile!
	if (o->getID() == shotBy->getID()) {
		return;
	}
	o->addHealth(-damage);
}