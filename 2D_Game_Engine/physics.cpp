#include "physics.h"
#include "object.h"
#include "variables.h"

Physics::Physics() {}

Physics::~Physics() {}

void Physics::startPhysics(float grav, int fric) {
	gravity = grav;
	friction = fric;
	timescale = 1;
}

void Physics::setPhysics(float gravity, int friction) {
	gravity = gravity;
	friction = friction;
	
}

//TODO: EDGE DETECTION??? 

void Physics::applyPhysics(Object* o) {
	//Physics calculations
	if (o->getPhysState() == obj_physics) {
		SDL_Rect* rect = o->getDestination();
		double xvel = o->getXVelocity();
		double yvel = o->getYVelocity();

		yvel = yvel + gravity;

		//Other physics properties can go down here

		rect->x = rect->x + xvel * timescale;
		rect->y = rect->y + yvel * timescale;

		o->setDestination(rect);
		o->setVelocity(xvel, yvel);
	}
}