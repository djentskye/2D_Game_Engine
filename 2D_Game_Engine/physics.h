#ifndef PHYSICS_H
#define PHYSICS_H

#pragma once

#include "object.h"
#include "variables.h"

class Physics
{
public: 
	Physics();
	~Physics();
	void startPhysics(float gravity, int friction);
	void setPhysics(float gravity, int friction);
	void applyPhysics(Object* o);

private:
	float gravity;
	int friction;
	double timescale;
};

#endif