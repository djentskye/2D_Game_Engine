#include "console.h"
#include <SDL_keycode.h>
#include "fonts.h"
#include "../game.h"
#include "../commands.h"

//Private static variables
static int textHeight, textWidth;
static SDL_Color textColor, backgroundColor, cursorColor;
static std::string textFont;
static int backgroundOpacity;
static int numLines, maxLines;
static int cursorWidth, cursorHeight;
static bool showConsole;
static std::string currentCommand;
static std::map<int, Object*>* backgroundObjMap;
static std::list<Object*>* textObjMap;
static Object* cursor;

Console::Console() {}

Console::~Console() {}

void Console::init(int text_h, int text_w, SDL_Color text_color, std::string text_font, 
				   SDL_Color background_color, int background_opacity) {
	textHeight = text_h;
	textWidth = text_w;
	textColor = text_color;
	textFont = text_font;
	backgroundColor = background_color;
	backgroundOpacity = background_opacity;
	numLines = 1;
	maxLines = 5;
	cursorWidth = 3;
	cursorHeight = 16;
	showConsole = false;
	backgroundObjMap = new std::map<int, Object*>();
	textObjMap = new std::list<Object*>();
	currentCommand = "";
	cursor = new Object();
	cursor->setX(1);
	cursor->setY(1);
	cursor->setWidth(cursorWidth);
	cursor->setHeight(cursorHeight);
	//Set the cursor color equal to the text color, for now
	cursorColor = text_color;
}

void Console::openConsole() {
	//Keyboard inputs will automatically go to the console

	//Reset some needed variables
	numLines = 1;
	currentCommand = "";
	cursor->setX(1);
	cursor->setY(1);
	backgroundObjMap = new std::map<int, Object*>();
	textObjMap = new std::list<Object*>();

	//Show console and allow rendering
	showConsole = true;
}

void Console::closeConsole() {
	//Stop showing console
	showConsole = false;
}

//TODO: Testing
void Console::writeChar(int sym) {
	currentCommand += (char)sym;

	std::string cString{(char)sym};

	//Create our character object
	Object* newChar = new Object();
	newChar->setDestination((textWidth+1) * (currentCommand.length()-1), (numLines-1) * (textHeight+1), textWidth, textHeight);
	
	//Get the character texture
	newChar->setTexture(Fonts::getRenderedText(cString, textFont, textHeight, textColor));

	//We will use the depth to store which row a letter is on
	newChar->setDepth(1);

	//Put our character object in the textObjMap
	textObjMap->push_back(newChar);

	cursorRight();
}

void Console::newLine() {
	//Run the command present in the text bar
	Commands::runCommand(currentCommand);

	//Reset the currentCommand string
	currentCommand = "";

	//If we are at our max number of lines, start removing the oldest lines!
	if (numLines == maxLines) {
		std::list<Object*>::iterator it;
		for (it = textObjMap->begin(); it != textObjMap->end(); ++it) {
			if ((*it)->getY() < 2) {
				//Remove the top row of text textures
				it = textObjMap->erase(it);
			}
			else {
				//Move the textures up to the next line
				(*it)->setY((*it)->getY() - (textHeight + 1));
				(*it)->setDepth((*it)->getDepth()+1);
			}
		}

		/*
		for (Object* o : *textObjMap) {
			if (o->getY() < 2) {
				//Remove the top row of text textures
				textObjMap->remove(o);
			}
			else {
				//Move the textures up to the next line
				o->setY(o->getY()- (textHeight + 1));
			}
		}*/
		cursorResetX();

		currentCommand = "";
	}
	else {
		numLines++;
		cursorDown();
		cursorResetX();

		currentCommand = "";

		std::list<Object*>::iterator it;
		for (it = textObjMap->begin(); it != textObjMap->end(); ++it) {
			(*it)->setDepth((*it)->getDepth() + 1);
		}

		//TODO: Add backgrounds!!
		//Object* newBackgroundTile = 
		//backgroundObjMap->emplace();
	}
}

std::map<int, Object*>* Console::getBackgroundObjMap() {
	return backgroundObjMap;
}

std::list<Object*>* Console::getTextObjMap() {
	return textObjMap;
}

void Console::cursorLeft() {
	if (cursor->getX() > (textWidth + 1)) {
		cursor->setX(cursor->getX() - (textWidth + 1));
	}
}

void Console::cursorRight() {
	if (cursor->getX() < Game::getWindowWidth() - (textWidth+1)) {
		cursor->setX(cursor->getX() + (textWidth + 1));
	}
}

void Console::cursorResetX() {
	cursor->setX(1);
}

void Console::cursorDown() {
	cursor->setY(cursor->getY() + (textHeight + 1));
}

Object* Console::getCursorObj() {
	return cursor;
}

bool Console::consoleShowing() {
	return showConsole;
}

SDL_Color Console::getCursorColor() {
	return cursorColor;
}

void Console::backspace() {

	cursorLeft();

	if (currentCommand.length() > 0) {
		//Remove the character to the left of the cursor
		int charToRemove = ((cursor->getX() - 1) / (textWidth + 1)) -1;
		currentCommand.erase(charToRemove, 1);
		/*
		//Get the iterator for the beginning of our command, and find the element just before our cursor
		std::list<Object*>::iterator it = textObjMap->begin();
		for (int i = 0; i < charToRemove; i++) {
			it++;
		}

		//Remove the element to the left of our cursor
		textObjMap->remove(*it);

		//Move all elements after the character we want to erase to the left
		for (it; it != textObjMap->end(); ++it) {
			(*it)->setX((*it)->getX() - textWidth);
		}
		*/

		//if (currentCommand.length() == 0) {
			//textObjMap->erase();
		//}

		int currentChar = 0;
		for (std::list<Object*>::iterator it = textObjMap->begin(); it != textObjMap->end(); ++it) {
			//Make sure we're on the right line!
			if ((*it)->getDepth() == 1) {
				//Make sure this is the right character
				if (currentChar == charToRemove) {
					//If it is the first character in the string, prevent from crashing!
					if (textObjMap->size() == 1) {
						textObjMap->clear();
						break;
						break;
					}
					if (currentChar >= currentCommand.length() - 1) {
						textObjMap->erase(it);
						break;
					}
					else {
						it = textObjMap->erase(it);
					}
				}
				else if (currentChar > charToRemove) {
					(*it)->setX((*it)->getX() - textWidth);
				}
				currentChar++;
			}
		}
	}
}