#pragma once
#include <iostream>
#include <map>
#include "object.h"
#include "renderer.h"
#include "physics.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	static void addObject(Object* obj);
	void initObjects();
	void updateObjects();
	void renderObjects(Renderer r);
	//Object* getObject(std::string oName);
	Object* getObject(int index);
	static void destroyObject(Object* obj);
	void destroyObjectByID(int objID);

private:
	//int counter;
	Physics physics;
};

