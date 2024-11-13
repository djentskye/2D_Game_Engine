///////////////////////////////////////////////////////////////
// objectmanager.cpp
// 
// This is the object manager class, which keeps track of all objects currently 
// in memory. Anything that is actively being updated or rendered must be stored in
// this class's objMap. The class is mostly used for rendering, updating positions 
// for physics and movement, and generally keeping track of anything that parts of 
// the engine would need to access. 
///////////////////////////////////////////////////////////////

#include "objectmanager.h"
#include "renderer.h"

static std::map<int, Object*> objMap;
static int counter;


//The engine should create objects through an object manager. 

//Every single object rendered in the engine must have a texture and an 
//SDL_Rect* dstrect, which contains the object's location in a scene. 


ObjectManager::ObjectManager()
{
	counter = 0;

	//This feels like an unhinged spot to initialize the physics at. 
	//but here we are. 
	physics.startPhysics(0.004f, 1);
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
void ObjectManager::addObject(Object* obj)
{
	//Should we have this show depth instead, so then we can sort 
	//and display everything in the correct order?
	//objMap.insert(std::pair<int,Object>(counter, obj));

	//Insert the object to the objMap using its objID, which it creates itself. 
	//This ensures there is no difference in how we track id's. 
	objMap.insert(std::pair<int, Object*>(obj->getID(), obj));
	
	//Add one to the current object counter
	counter++;
}

/**
 * Removes an object from the object manager and destroys the object
 * 
 * @param Object obj
 */
void ObjectManager::destroyObject(Object* obj)
{
	//Remove the specified object from the objMap
	objMap.erase(obj->getID());

	//TODO: Find a way to uninitialize objects in their own class

	//Subtract one from the current object counter
	counter--;
}

void ObjectManager::destroyObjectByID(int objID)
{
	//Remove the specified object from the objMap using its ID
	objMap.erase(objID);

	//Subtract one from the current object counter
	counter--;
}

void ObjectManager::initObjects()
{
	//Why do we even have this? For a level load, to initialize all objects 
	//(ex: scripting)
}

/**
 * Updates all objects, mostly based on input
 */
void ObjectManager::updateObjects()
{
	//Reset the collision bounds
	physics.resetCollisionList();

	//Loop over each element and apply updates to them
	auto it = objMap.begin();
	while (it != objMap.end()) {
		Object* obj = (*it).second;
		if (!physics.applyPhysics((*it).second)) {
			it = objMap.erase(it);
		}
		else {
			if (obj->isEntity()) {
				obj->update();
			}

			//Checks to make sure we don't accidentally increment something we can't
			if (it == objMap.end()) {
				break;
			}
			else {
				++it;
			}
		}
	}
}

/**
 * Renders all objects
 *
 * @param Renderer r
 */
void ObjectManager::renderObjects(Renderer r)
{
	//TODO: fix
	//r.render();
}

/**
 * Returns the object at a specific index
 *
 * @param int index
 */
Object* ObjectManager::getObject(int index)
{
	return objMap.find(index)->second;
}