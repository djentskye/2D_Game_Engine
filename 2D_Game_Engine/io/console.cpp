///////////////////////////////////////////////////////////////
// io/console.cpp
// 
// This is the console class, which handles everything needed for the console. It 
// handles input, selecting and storing characters, displaying the right textures, 
// and generally displaying graphics as appropriate. It is static, though needs to 
// be initialized. 
///////////////////////////////////////////////////////////////

#include "console.h"
#include <SDL_keycode.h>
#include "fonts.h"
#include "../game.h"
#include "../commands.h"
#include "../texture.h"

//Private static variables
static int textHeight, textWidth;
static SDL_Color textColor, backgroundColor, cursorColor;
static std::string textFont;
static int backgroundOpacity;
static int numLines, maxLines;
//Width and height of our cursor
static int cursorWidth, cursorHeight;
static bool showConsole;
//String containing the current command's text
static std::string currentCommand;
//Object for displaying the console background
static Object* backgroundObj;
//List of objects which make up the text on our console
static std::list<Object*>* textObjMap;
static Object* cursor;
//Is the user holding shift
static bool shift;
//The amount to move the background down upon every command run
static int backgroundShiftIncrementSize;
//The Y location of the background
static int requestedBackgroundY;

Console::Console() {}

Console::~Console() {}

/**
 * Initializes the console
 * 
 * @param int text_h					Text height
 * @param int text_w					Text width
 * @param SDL_Color text_color			Text color
 * @param std::string text_font			Text font (must be a supported font)
 * @param SDL_Color background_color	Console background color
 * @param int background_opacity		Console background opacity
 */
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
	backgroundShiftIncrementSize = (textHeight + 1);

	//Set up the background
	backgroundObj = new Object();
	backgroundObj->setTexture(Texture::getTexture("assets/textures/console_background.png"));
	backgroundObj->setDestination(0, -((textHeight + 1) * maxLines), Game::getWindowWidth(), ((textHeight + 1) * maxLines));
	
	textObjMap = new std::list<Object*>();

	currentCommand = "";

	//Set up the cursor
	cursor = new Object();
	cursor->setX(1);
	cursor->setY(1);
	cursor->setWidth(cursorWidth);
	cursor->setHeight(cursorHeight);

	//Set the cursor color equal to the text color, for now
	cursorColor = text_color;
	shift = false;
	requestedBackgroundY = -((textHeight + 1) * maxLines);
}

/**
 * Opens the console
 */
void Console::openConsole() {
	//Keyboard inputs will automatically go to the console

	//Reset some needed variables
	numLines = 1;
	currentCommand = "";
	cursor->setX(1);
	cursor->setY(1);
	backgroundObj->setDestination(0, -((textHeight + 1) * maxLines), Game::getWindowWidth(), ((textHeight + 1) * maxLines));
	textObjMap = new std::list<Object*>();

	//Show console and allow rendering
	showConsole = true;
}

/**
 * Closes the console
 */
void Console::closeConsole() {
	//Stop showing console
	showConsole = false;
	backgroundObj->setDestination(-2, -2, -1, -1);

	requestedBackgroundY = -((textHeight + 1) * maxLines);
}

/**
 * Writes a character to the console. 
 * 
 * @param int sym, ASCII key code
 */
void Console::writeChar(int sym) {

	//Apply shift if it is currently held
	//TODO: Expand functionality to include more keys. 
	if (shift) {
		if (sym >= 97 && sym <= 122) {
			sym -= 32;
		}
		else if (sym == '-') {
			sym = '_';
		}
		else if (sym >= 91 && sym <= 93) {
			sym += 32;
		}
		else if (sym == '=') {
			sym = '+';
		}
	}
	if (sym == SDLK_ESCAPE) {
		closeConsole();
	}

	//Add this character to our string
	currentCommand += (char)sym;

	std::string cString{(char)sym};

	//Create our character object
	Object* newChar = new Object();
	newChar->setDestination((textWidth+1) * (currentCommand.length()-1), (numLines-1) * 
							(textHeight+1), textWidth, textHeight);
	
	//Get the character texture
	newChar->setTexture(Fonts::getRenderedText(cString, textFont, textHeight, textColor));

	//We will use the depth to store which row a letter is on
	newChar->setDepth(1);

	//Put our character object in the textObjMap
	textObjMap->push_back(newChar);

	cursorRight();
}

void Console::pushThisLineUp() {
	//If we are at our max number of lines, start removing the oldest lines!
	if (numLines == maxLines) {
		std::list<Object*>::iterator it;
		for (it = textObjMap->begin(); it != textObjMap->end(); it) {
			if ((*it)->getDepth() == maxLines) {
				if (textObjMap->size() == 1) {
					textObjMap->erase(it);
					break;
				}
				else {
					//Remove the top row of text textures
					it = textObjMap->erase(it);
				}
			}
			else {
				//Move the textures up to the next line
				(*it)->setY((*it)->getY() - (textHeight + 1));
				(*it)->setDepth((*it)->getDepth() + 1);
				it++;
			}

			if (it == textObjMap->end()) {
				break;
			}
		}

		cursorResetX();

		//currentCommand = "";
	}
	else {
		numLines++;
		cursorDown();
		cursorResetX();

		//currentCommand = "";

		std::list<Object*>::iterator it;
		for (it = textObjMap->begin(); it != textObjMap->end(); ++it) {
			(*it)->setDepth((*it)->getDepth() + 1);
		}

		if (numLines == 2) {
			requestedBackgroundY += backgroundShiftIncrementSize;
		}

		backgroundObj->setVelocity(0, 0.8);
		requestedBackgroundY += backgroundShiftIncrementSize;
	}
}

/**
 * Creates a new line in the console. This should occur when enter/return is pressed. 
 */
void Console::newLine() {

	pushThisLineUp();

	//Run the command present in the text bar
	Commands::runCommand(currentCommand);

	//Reset the currentCommand string
	currentCommand = "";
}

Object* Console::getBackgroundObj() {
	return backgroundObj;
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

/**
 * Backspace function. Gets called when the user presses backspace!
 */
void Console::backspace() {

	//Move the cursor left once
	cursorLeft();


	if (currentCommand.length() > 0) {
		//Remove the character to the left of the cursor
		int charToRemove = (((int)cursor->getX() - 1) / (textWidth + 1));
		currentCommand.erase(charToRemove, 1);

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
					} else if (currentChar >= currentCommand.length() - 1) {
						textObjMap->erase(it);
						break;
					}
					else {
						//TODO: THIS is skipping one character. 
						it = textObjMap->erase(it);
						it--;
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

/**
 * Sets whether shift is on or not. True if it's on, false if it's off. 
 */
void Console::setShift(bool b) {
	shift = b;
}

/**
 * Updates the console. 
 */
void Console::update() {
	//Update the position of the background object. 
	if (backgroundObj->getDestination()->y < requestedBackgroundY) {
		backgroundObj->update();
	}
}

void Console::print(std::string str) {

	std::string outputStr = "> " + str;

	Object* outputLine = new Object();

	outputLine->setDestination(0, (numLines-1) *
	(textHeight + 1), ((textWidth+1) * (str.length() + 2)), textHeight);
	


	//Get the string texture
	outputLine->setTexture(Fonts::getRenderedText(outputStr, textFont, textHeight, textColor));

	//We will use the depth to store which row a letter is on
	outputLine->setDepth(1);

	//Put our character object in the textObjMap
	textObjMap->push_back(outputLine);
	
	pushThisLineUp();
}

bool Console::isOpen() {
	return showConsole;
}