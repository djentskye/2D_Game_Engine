#pragma once
#include <iostream>
#include <map>
#include "object.h"
#include "renderer.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	void addObject(Object obj);
	void initObjects();
	void updateObjects();
	void renderObjects(Renderer r);
	//Object* getObject(std::string oName);
	Object* getObject(int index);

private:
	std::map<int, Object> objMap;
	int counter;
};

