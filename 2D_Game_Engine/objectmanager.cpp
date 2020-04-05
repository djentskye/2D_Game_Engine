#include "objectmanager.h"
#include "renderer.h"

std::map<int, Object> staticObjMap;
int counter;

ObjectManager::ObjectManager()
{
	counter = 0;
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::addObject(Object obj)
{
	objMap.insert(std::pair<int,Object>(counter, obj));
	
	counter++;
}

void ObjectManager::initObjects()
{
	//Why do we even have this? For a level load, to initialize all objects (ex: scripting)
}

void ObjectManager::updateObjects()
{
	for (std::pair<int, Object> element : objMap) {
		//Update forces (gravity)
		//Update movement (scripted)
		///Update player input /where do we want this in the chain?
		///^this probably doesn't belong in the object manager
	}
}

//void ObjectManager::renderObjects(Renderer r)
//{
//	for (std::pair<int, Object> element : objMap) {
//		try
//		{
//			//element.second.renderObject();
//		}
//		catch (const std::exception&)
//		{
//			std::cout << "Could not render object " << element.second.getName() << ", id " <<  //Does this syntax work?
//				element.first << "." << std::endl;
//		}
//	}
//}

void ObjectManager::renderObjects(Renderer r)
{
	r.render();
}

Object* ObjectManager::getObject(int index)
{
	return &objMap.find(index)->second;
}