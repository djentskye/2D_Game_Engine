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


/**
 * Applies physics to an object. Should be called on every object which should have physics
 * interactions. Returns false if the object should be destroyed. 
 */
bool Physics::applyPhysics(Object* o) {
	//Physics calculations
	SDL_Rect* rect = o->getDestination();
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
			SDL_Rect* r = collisionList[i]->getDestination();



			//If the two objects are in each other, push apart!
			if (SDL_HasIntersection(r, rect)) {
				//Find the difference between their respective centers
				//double diffx = ((r->x + r->w / 2) - (rect->x + rect->w / 2));
				//double diffy = ((r->y + r->h / 2) - (rect->y + rect->h / 2));

				double magnitude = 0.95;
				//double magnitude = 2;

				//We just have to push back on the object with the same amount of force it's exerting 
				// on us
				//Get the angle of the object's velocity
				double oppositeAngle = std::fmod(collisionList[i]->getVelocityAngle()+180, 360);
				double perpendicular = std::fmod(o->getRotation(), 90);

				//Find the new angle that the object should be pushed
				double newRotate = perpendicular - oppositeAngle;
				double newAngle = perpendicular + newRotate;

				double x_component = std::sin(newAngle) * magnitude;
				double y_component = std::cos(newAngle) * magnitude;

 				double toAccelX = -collisionList[i]->getXVelocity() + x_component;
				double toAccelY = -collisionList[i]->getYVelocity() + y_component;
				//double toAccelX = x_component;
				//double toAccelY = y_component;
				
				//Since this is a static object, we need to exert all this force on the other one. 
				collisionList[i]->addToVelocity(toAccelX, toAccelY);
				collisionList[i]->addToRotationVelocity(newRotate);
			}

			//If the two objects have not collided but will colide after applying velocity, calculate
			//TODO

		}

		//Add o's rect to the collisionList
		collisionList.push_back(o);
	}
	if (o->getPhysState() == obj_dynamic) {
		//Loop through collisionList and see if we collide with anyone
		for (int i = 0; i < collisionList.size(); i++) {
			SDL_Rect* r = collisionList[i]->getDestination();



			//If the two objects are in each other, push apart!
			if (SDL_HasIntersection(r, rect)) {
				
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
			SDL_Rect* r = collisionList[i]->getDestination();



			//If the two objects are in each other, push apart!
			if (SDL_HasIntersection(r, rect)) {
				
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
		rect->x = rect->x + xvel * timescale;
		rect->y = rect->y + yvel * timescale;

		//o->setDestination(rect);
		o->setX(rect->x);
		o->setY(rect->y);
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

