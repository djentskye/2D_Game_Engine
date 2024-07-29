#ifndef PROJECTILE_H
#define PROJECTILE_H

#pragma once

#include <iostream>
#include "SDL.h"
#include "object.h"

typedef enum
{
	PROJ_GREEN = 0,
	PROJ_ORANGE = 1
} PROJ_TypeCode;

class Projectile : public Object
{
public:
	Projectile(Object* from);
	Projectile(Object* from, PROJ_TypeCode type, double xvel, double yvel, double dmg);
	~Projectile();
	void setDamage(double dmg);
	bool onCollision(Object* o);
	void update();

private:
	double damage;
	Object* shotBy;
	PROJ_TypeCode projType;
	bool dissappearOnHit;
	int rendererValue;
	bool destroyed;

};

#endif