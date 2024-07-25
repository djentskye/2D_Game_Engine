#ifndef PROJECTILE_H
#define PROJECTILE_H

#pragma once

#include <iostream>
#include "object.h"

class Projectile : public Object
{
public:
	Projectile(Object* from);
	~Projectile();
	void onCollision(Object* o);

private:
	double damage;
	Object* shotBy;

};

#endif