#ifndef PHYSICS_H
#define PHYSICS_H

#pragma once

#include "object.h"
#include "variables.h"
#include <iostream>
#include <vector>

class Physics
{
public: 
	Physics();
	~Physics();
	void startPhysics(float gravity, int friction);
	void setPhysics(float gravity, int friction);
	void setGravity(float g);
	void setFriction(int f);
	void setTimescale(double t);
	void applyPhysics(Object* o);
	void resetCollisionList();

private:
	float gravity;
	int friction;
	double timescale;
	std::vector<Object*> collisionList;
};

#endif