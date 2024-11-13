///////////////////////////////////////////////////////////////
// renderer.cpp
// 
// This is the renderer, which stores our SDL_Renderer object pointer, the render 
// queue, and other relevant rendering information. It must be initialized in 
// game.cpp prior to use. Anything that must be rendered shoud be put into the 
// render queue, making this class essential for creating new objects.
///////////////////////////////////////////////////////////////

#include "renderer.h"

//#include <SDL.h>
//#include <glew.h>
//#include <SDL_opengl.h>
//#include <gl/glu.h>

#include <iostream>
#include "player.h"
#include "io/console.h"
#include "game.h"
#include "ui/menus.h"

static SDL_Renderer* renderer;
static std::map<int, Object*> renderQueue;
static std::map<int, Object*> consoleRenderQueue;

//int gProgramID;
//unsigned int gVBO;
//unsigned int gIBO;

GLuint gProgramID = 0;
GLuint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gVAO = 0;
//GLuint gIBO = 0;

SDL_GLContext gContext;
//SDL_Window* win;

GLuint vertexShader;
GLuint fragShader;
GLuint shaderProgram;




//Load hardcoded shaders
const GLchar* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

const GLchar* fragSource = R"glsl(
    #version 150 core

	out vec4 outColor;

	void main()
	{
		outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
)glsl";


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::printProgramLog(GLuint program) {
	if (glIsProgram(program)) {
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		char* infoLog = new char[maxLength];

		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0) {
			//Print the log
			printf("%s\n", infoLog);
		}

		//Deallocate
		delete[] infoLog;
	}
	else {
		std::cout << "Could not print program log. Parameter is not a program." << std::endl;
	}
}

void Renderer::printShaderLog(GLuint shader) {
	if (glIsShader(shader)) {
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		char* infoLog = new char[maxLength];

		glGetProgramInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0) {
			//Print the log
			printf("%s\n", infoLog);
		}

		//Deallocate
		delete[] infoLog;
	}
	else {
		std::cout << "Could not print shader log. Parameter is not a shader." << std::endl;
	}
}

/**
 * Initializes OpenGL
 * 
 * Big thanks to lazyfoo.net for providing a lot of the starting concepts and 
 * structure for this code! It was significantly altered from the original on 
 * their website, but their site made this process a lot easier. (:
 */
bool Renderer::initOpenGL() {
	//gProgramID = glCreateProgram();

	//glUseProgram(gProgramID);

	/*
	//Create a vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get the vertex shader source; for now this will be hardcoded
	const GLchar* vertexShaderSource[] = { "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4(LVertexPos2D.x, LVertexPos2D.y, 0, 1); }" };

	//Set vertex shader source
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//Compile vertex shader source
	glCompileShader(vertexShader);

	//Check the shader we compiled for errors!
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
	if (vShaderCompiled != GL_TRUE) {
		std::cout << "Failed to compile vertex shader";
		std::cout << vertexShader << std::endl;

		printShaderLog(vertexShader);

		return false;
	}
	//Attach the vertex shader to our program
	glAttachShader(gProgramID, vertexShader);

	//Create a frag shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Get the frag shader source
	const GLchar* fragmentShaderSource[] = { "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }" };

	//Set the frag shader source
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

	//Compile the frag shader source
	glCompileShader(fragmentShader);

	//Check for errors
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE) {
		std::cout << "Failed to compile fragment shader";
		std::cout << fragmentShader << std::endl;

		printShaderLog(fragmentShader);

		return false;
	}
	//Attach the fragment shader to our program
	glAttachShader(gProgramID, fragmentShader);

	//Link the program
	glLinkProgram(gProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE) {
		std::cout << "Failed to link program";
		std::cout << gProgramID << std::endl;

		printProgramLog(gProgramID);

		return false;
	}


	//Get the vertex attribute location
	GLint gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
	if (gVertexPos2DLocation == -1) {
		std::cout << "LVertexPos2D is not a valid glsl program variable" << std::endl;
		return false;
	}
	*/
	//Initialize clear color
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	//VBO data here! vertex data formatted in a GLfloat array
	GLfloat tempVertexData[] =
	{
		 0.0f,  0.5f, //vertex 1 (x, y)
		 0.5f, -0.5f, //vertex 2 (x, y)
		-0.5f, -0.5f //vertex 3 (x, y)
	};

	//IBO data here
	//GLuint indexData[] = { 0, 1, 2, 3 };

	//Create the VAO
	glGenVertexArrays(1, &gVAO);
	//Start using the VAO
	glBindVertexArray(gVAO);

	//Create the VBO
	glGenBuffers(1, &gVBO);
	//Make the VBO the active object
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	//Copy the vertex data onto our VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(tempVertexData), tempVertexData, GL_STATIC_DRAW);

	//Create a shader object for our vert shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Load data into our shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the vert shader
	glCompileShader(vertexShader);



	//Create a shader object for our frag shader
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Load data into our shader object
	glShaderSource(fragShader, 1, &fragSource, NULL);
	//Compile the frag shader
	glCompileShader(fragShader);

	//Error checking for vertex shader
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE) {
		std::cout << "Failed to compile vertex shader";
		std::cout << vertexShader << std::endl;

		printShaderLog(vertexShader);

		return false;
	}

	//Error checking for fragment shader
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE) {
		std::cout << "Failed to compile fragment shader";
		std::cout << fragShader << std::endl;

		printShaderLog(fragShader);

		return false;
	}

	//Create a shader program that combines both of our shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	/*glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);

	//Specify which output is written to which framebuffer on our frag shader
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	//Link the program
	glLinkProgram(shaderProgram);
	//Use the shaders
	glUseProgram(shaderProgram);*/

	//Grab a reference to the position parameter location so we can link our 
	//inputs and whatnot
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");

	//Enable the vertex attribute array
	glEnableVertexAttribArray(posAttrib);
	//Specify how the data for this input is retrieved from our array of vertices
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);








	/*
	//Create the IBO
	glGenBuffers(1, &gIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	//This particular line should be offloaded to another function!
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
	*/

	return true;
}

/*void GLAPIENTRY Renderer::MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}*/

/**
 * Initialize the renderer
 *
 * @param SDL_Window* window
 */
void Renderer::init(SDL_Window* window, SDL_GLContext context) {





	gContext = context;

	//win = window;

	//Create the GL context attached to our window
	//gContext = SDL_GL_CreateContext(window);
	//SDL_GL_MakeCurrent(window, gContext);

	//Check to make sure everything went ok
	if (gContext == NULL) {
		std::cout << "Failed to create OpenGL context. SDL Error: ";
		std::cout << SDL_GetError() << std::endl;

		return;
	}
	
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cout << "Failed to initialize GLEW context. GLEW Error: ";
		std::cout << glewGetErrorString(glewError) << std::endl;

		return;
	}

	glEnable(GL_DEBUG_OUTPUT);
	//glDebugMessageCallback(MessageCallback, 0);

	if (!initOpenGL()) {
		std::cout << "Failed to initialize OpenGL. ";

		return;
	}
}

/**
 * Destroy the renderer
 */
void Renderer::exit() {
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	glDeleteBuffers(1, &gVBO);

	glDeleteVertexArrays(1, &gVAO);

	SDL_GL_DeleteContext(gContext);
}

/**
 * Renders the console
 */
void Renderer::renderConsole() {
	//TODO: This is super clunky lol, in the future we should have pointers in this class.
	Object* backgroundObj = Console::getBackgroundObj();
	std::list<Object*> textObjMap = *Console::getTextObjMap();

	//Render the background
	SDL_RenderCopy(renderer, backgroundObj->getTexture(), NULL, backgroundObj->getDestination());

	//Render the cursor
	SDL_Color cursorColor = Console::getCursorColor();
	if (Game::getTick() % 50 < 25) {
		SDL_SetRenderDrawColor(renderer, cursorColor.r, cursorColor.g, cursorColor.b, 255);
	}
	else {
		SDL_SetRenderDrawColor(renderer, cursorColor.r, cursorColor.g, cursorColor.b, 0);
	}

	SDL_Rect* test = Console::getCursorObj()->getDestination();

	SDL_RenderDrawRect(renderer, Console::getCursorObj()->getDestination());

	//Render the text
	for (Object* element : textObjMap) {
		SDL_RenderCopy(renderer, element->getTexture(), NULL, element->getDestination());
	}
}

//TODO: [REND] Add a render sorter
//TODO: [REND] Multiple obj layers
/**
 * Render to the screen
 *
 * This basically processes all of our rendering. Render order should be adjusted
 * here, and all objects are rendered from the render queue. 
 */
void Renderer::render(SDL_Window* window)
{
	glUseProgram(shaderProgram);
	//std::cout << glGetError() << std::endl;

	//Clear color buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	SDL_GL_SwapWindow(window);
	







	//Bind program
	//glUseProgram(gProgramID);

	//Enable vertex position
	//glEnableVertexAttribArray(gVertexPos2DLocation);

	//Set vertex data
	//glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	//glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), NULL);

	//set index data and render
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);


	//Disable vertex position
	//glDisableVertexAttribArray(gVertexPos2DLocation);

	//Unbind program
	//glUseProgram(NULL);

	


	/*
	//Render the menus if they are currently showing
	if (Gamestates::getGamestate() == gs_menu ||
		Gamestates::getGamestate() == gs_pausemenu) {
		Menus::renderActiveMenu();
		SDL_RenderPresent(renderer);
		return;
	}

	//Literally render everything here
	//TODO: [REND] Implement a system for render order
	//TODO: [REND] Render background

	//TODO: [REND] Get an iterator to return things in order from lowest-highest depth
	for (std::pair<int, Object*> element : renderQueue) {
		//SDL_RenderCopy(renderer, element.second->getTexture(), NULL, element.second->getDestination());
		SDL_RenderCopyEx(renderer, element.second->getTexture(), NULL, element.second->getDestination(), element.second->getRotation(), NULL, element.second->getTextureFlip());
	}

	//Render the console if it's currently showing
	if (Console::consoleShowing()) {
		//Display the menu in the background if it was showing last
		if (Gamestates::getPriorGamestate() == gs_menu) {
			Menus::renderActiveMenu();
		}

		//Display the game in the background if it was showing last
		if (Gamestates::getPriorGamestate() == gs_game) {
			//??????????????
		}

		renderConsole();
	}

	SDL_RenderPresent(renderer);
	*/
}

//We want this to return a POINTER to the renderer; is this correct?
/**
 * Returns the renderer (?)
 */
SDL_Renderer* Renderer::getRenderer()
{
	return renderer;
}

/**
 * Adds an object to the render queue automatically
 *
 * This should be used for most rendering, though not if objects are intended to
 * be in a specific order
 *
 * @param Object o
 */
int Renderer::addToRenderQueue(Object* o)
{
	//Eventually we will need a method to change the depth by removing from render queue and re-adding
	//renderQueue.insert(std::pair<int, Object*>(renderQueue.size()+1, o));
	renderQueue.insert(std::pair<int, Object*>(o->getID(), o));

	return o->getID();
}

/**
 * Adds an object to the render queue to a specific location
 *
 * @param int i
 * @param Object o
 */
void Renderer::addToRenderQueue(int i, Object o)
{
	//Eventually we will need a method to change the depth by removing from render queue and re-adding
	renderQueue.insert(std::pair<int, Object*>(i, &o)).first; //??? &
}

/**
 * Removes an object from the render queue
 * 
 * @param Object* o
 */
void Renderer::removeFromRenderQueue(Object* o) {
	renderQueue.erase(o->getID());
}