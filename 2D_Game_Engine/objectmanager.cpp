#include "objectmanager.h"
#include "renderer.h"

std::map<int, Object> staticObjMap;
int counter;


//The engine should create objects through an object manager. 


ObjectManager::ObjectManager()
{
	counter = 0;
}


ObjectManager::~ObjectManager()
{
}

/**
 * Adds an object to the object manager
 *
 * Increments the counter, and adds to the map with the index being
 * the counter value. 
 *
 * @param Object obj
 */
void ObjectManager::addObject(Object obj)
{
	//Should we have this show depth instead, so then we can sort 
	//and display everything in the correct order?
	objMap.insert(std::pair<int,Object>(counter, obj));
	
	counter++;
}

void ObjectManager::initObjects()
{
	//Why do we even have this? For a level load, to initialize all objects (ex: scripting)
}

/**
 * Updates all objects, mostly based on input
 */
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

/**
 * Renders all objects
 *
 * @param Renderer r
 */
void ObjectManager::renderObjects(Renderer r)
{
	r.render();
}

/**
 * Returns the object at a specific index
 *
 * @param int index
 */
Object* ObjectManager::getObject(int index)
{
	return &objMap.find(index)->second;
}