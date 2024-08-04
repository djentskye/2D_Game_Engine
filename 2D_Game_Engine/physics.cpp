#include <iostream>
#include "physics.h"
#include "object.h"
#include "variables.h"
#include <cmath>
#include "projectile.h"

Physics::Physics() {}

Physics::~Physics() {}

/**
 * Starts the physics by setting some important variables. 
 */
void Physics::startPhysics(float grav, int fric) {
	gravity = grav;
	friction = fric;
	timescale = 0.6;
}

/**
 * Sets important physics variables. 
 */
void Physics::setPhysics(float gravity, int friction) {
	gravity = gravity;
	friction = friction;
}

void Physics::setGravity(float g) { gravity = g; }

void Physics::setFriction(int f) { friction = f; }

void Physics::setTimescale(double t) { timescale = t; }

//TODO: EDGE DETECTION??? 
void Physics::calculateCollisionStaticNonstatic(Object* o, Object* v) {
	//TODO: Store this  so we don't have to make this every time /:
	float RectLineInputs[4] = { v->getCenter().x,
							   v->getCenter().y,
							   v->getCenter().x - (v->getXVelocity() * timescale),
							   v->getCenter().y - (v->getYVelocity() * timescale),
	};

	int xDirection, yDirection;
	double rectBoundX, rectBoundY;
	double xdest = v->getX();
	double ydest = v->getY();
	if (RectLineInputs[2] > o->getCenter().x) {
		rectBoundX = o->getX() + o->getWidth();
		xDirection = 1;
		//If the collision is happening on x-axis, change xdest accordingly!!~
		if (xdest < rectBoundX) {
			xdest = rectBoundX;
		}
	}
	else {
		rectBoundX = o->getX();
		xDirection = -1;
		//Change xdest accordingly!!~
		if (xdest - v->getWidth() < rectBoundX) {
			xdest = rectBoundX - v->getWidth();
		}
	}
	if (RectLineInputs[3] > o->getCenter().y) {
		rectBoundY = o->getY() + o->getHeight();
		yDirection = 1;
		//Change ydest accordingly!!~
		if (ydest < rectBoundY) {
			ydest = rectBoundY;
		}
	}
	else {
		rectBoundY = o->getY();
		yDirection = -1;
		//Change ydest accordingly!!~
		if (ydest - v->getHeight() < rectBoundY) {
			ydest = rectBoundY - v->getHeight();
		}
	}

		//TODO: This is only kinda terrible now!!
	v->setDestination(xdest,
					  ydest,
					  v->getWidth(),
					  v->getHeight());
}

/**
 * Applies physics to an object. Should be called on every object which should have physics
 * interactions. Returns false if the object should be destroyed. 
 */
bool Physics::applyPhysics(Object* o) {
	//Physics calculations
	double x, y;
	x = o->getX();
	y = o->getY();
	SDL_Rect* rect = o->getDestination();
	//This is awful lol
	SDL_FRect frect = {(float)rect->x, (float)rect->y, (float)rect->w, (float)rect->h };
	double xvel = o->getXVelocity();
	double yvel = o->getYVelocity();

	//Gravity
	//if (o->getPhysState() == obj_physics) {
	//	yvel = yvel + gravity + yvel*gravity;
	//}

	//Other physics properties can go down here

	if (o->getPhysState() == obj_proj) {
		for (int i = 0; i < collisionList.size(); i++) {
			Object* r = collisionList[i];

			//If the two objects are in each other, see if you need to get rid of the projectile and 
			//deal damage!
			if (SDL_HasIntersection(r->getDestination(), rect)) {
				if (!((Projectile*)o)->onCollision(r)) {
					return false;
				}
			}
		}
	}

	//Collision detection
	//TODO: Optimize this some day lol
	if (o->getPhysState() == obj_static) {
		//Loop through collisionList and see if we collide with anyone
		for (int i = 0; i < collisionList.size(); i++) {
			Object* v = collisionList[i];

			if (v->getPhysState() == obj_dynamic || v->getPhysState() == obj_physics) {
				//If the two objects are in each other, push apart!

				if (SDL_HasIntersection(v->getDestination(), rect)) {
					calculateCollisionStaticNonstatic(o, v);
				}
			}
		}

		//Add o's rect to the collisionList
		collisionList.push_back(o);
	}
	if (o->getPhysState() == obj_dynamic) {
		//Loop through collisionList and see if we collide with anyone
		for (int i = 0; i < collisionList.size(); i++) {
			Object* v = collisionList[i];



			//If the two objects are in each other, push apart!
			if (SDL_HasIntersection(v->getDestination(), rect)) {
				calculateCollisionStaticNonstatic(v, o);
			}

			//If the two objects have not collided but will colide after applying velocity, calculate
			//TODO

		}

		//Add o's rect to the collisionList
		collisionList.push_back(o);
	}
	if (o->getPhysState() == obj_physics) {
		//Loop through collisionList and see if we collide with anyone
		for (int i = 0; i < collisionList.size(); i++) {
			Object* v = collisionList[i];



			//If the two objects are in each other, push apart!
			if (SDL_HasIntersection(v->getDestination(), rect)) {
				calculateCollisionStaticNonstatic(v, o);
			}

			//If the two objects have not collided but will colide after applying velocity, calculate
			//TODO

		}

		//Add o's rect to the collisionList
		collisionList.push_back(o);
	}

	//Update o's location
	phys_state physicsState = o->getPhysState();
	if (physicsState == obj_dynamic || physicsState == obj_physics || physicsState == obj_proj) {
		x = x + xvel * timescale;
		y = y + yvel * timescale;

		//o->setDestination(rect);
		o->setX(x);
		o->setY(y);
		o->setVelocity(xvel, yvel);

		/*if (o->getName() == "player") {
			int SDFKJLHSDKLJF = xvel;
			std::cout << "x = ";
			std::cout << SDFKJLHSDKLJF << std::endl;
		}*/
	}

	return true;
}

/**
 * Resets the collision list. This should be run between ticks, before or after collisions occur. 
 */
void Physics::resetCollisionList() {
	collisionList.clear();
}

