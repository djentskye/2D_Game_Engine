#include "physics.h"
#include "object.h"
#include "variables.h"
#include <cmath>

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
	SDL_Rect* rect = o->getDestination();
	double xvel = o->getXVelocity();
	double yvel = o->getYVelocity();

	//Gravity
	if (o->getPhysState() == obj_physics) {
		yvel = yvel + gravity;
	}

	//Other physics properties can go down here

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

				//We just have to push back on the object with the same amount of force it's exerting on us
				//Get the angle of the object's velocity
				double oppositeAngle = std::fmod(collisionList[i]->getVelocityAngle()+180, 360);
				double perpendicular = std::fmod(o->getRotation(), 90);

				//Find the new angle that the object should be pushed
				double newRotate = perpendicular - oppositeAngle;
				double newAngle = perpendicular + newRotate;

				double x_component = std::cos(newAngle) * magnitude;
				double y_component = std::sin(newAngle) * magnitude;

				double toAccelX = -collisionList[i]->getXVelocity() + x_component;
				double toAccelY = -collisionList[i]->getYVelocity() + y_component;
				
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
				//Find the difference between their respective centers
				//double diffx = ((r->x + r->w / 2) - (rect->x + rect->w / 2));
				//double diffy = ((r->y + r->h / 2) - (rect->y + rect->h / 2));

				double magnitude = 0.95;

				//We just have to push back on the object with the same amount of force it's exerting on us
				//Get the angle of the object's velocity
				double oppositeAngle = std::fmod(collisionList[i]->getVelocityAngle() + 180, 360);
				double perpendicular = std::fmod(o->getRotation(), 90);

				//Find the new angle that the object should be pushed
				double newRotate = perpendicular - oppositeAngle;
				double newAngle = perpendicular + newRotate;

				double x_component = std::cos(newAngle) * magnitude;
				double y_component = std::sin(newAngle) * magnitude;

				double toAccelX = -collisionList[i]->getXVelocity() + x_component;
				double toAccelY = -collisionList[i]->getYVelocity() + y_component;

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
	if (o->getPhysState() == obj_physics) {
		//Loop through collisionList and see if we collide with anyone
		for (int i = 0; i < collisionList.size(); i++) {
			SDL_Rect* r = collisionList[i]->getDestination();



			//If the two objects are in each other, push apart!
			if (SDL_HasIntersection(r, rect)) {
				//Find the difference between their respective centers
				//double diffx = ((r->x + r->w / 2) - (rect->x + rect->w / 2));
				//double diffy = ((r->y + r->h / 2) - (rect->y + rect->h / 2));

				double magnitude = 0.95;

				//We just have to push back on the object with the same amount of force it's exerting on us
				//Get the angle of the object's velocity
				double oppositeAngle = std::fmod(collisionList[i]->getVelocityAngle() + 180, 360);
				double perpendicular = std::fmod(o->getRotation(), 90);

				//Find the new angle that the object should be pushed
				double newRotate = perpendicular - oppositeAngle;
				double newAngle = perpendicular + newRotate;

				double x_component = std::cos(newAngle) * magnitude;
				double y_component = std::sin(newAngle) * magnitude;

				double toAccelX = -collisionList[i]->getXVelocity() + x_component;
				double toAccelY = -collisionList[i]->getYVelocity() + y_component;

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

	//Update o's location
	if (o->getPhysState() == obj_dynamic || obj_physics) {
		rect->x = rect->x + xvel * timescale;
		rect->y = rect->y + yvel * timescale;

		o->setDestination(rect);
		o->setVelocity(xvel, yvel);
	}
}

void Physics::resetCollisionList() {
	collisionList.clear();
}

