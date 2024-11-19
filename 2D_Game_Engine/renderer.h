#pragma once
#include "object.h"
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/glu.h>
#include <iostream>
#include <map>
#include "player.h"
#include "io/console.h"

//#pragma comment(lib, "glew32.lib")

class Renderer
{
public:
	Renderer();
	~Renderer();
	void init(SDL_Window* window, SDL_GLContext context);
	void exit();
	static void renderConsole();
	static void render(SDL_Window* window);
	static SDL_Renderer* getRenderer();
	static int addToRenderQueue(Object* o);
	static void addToRenderQueue(int i, Object o);
	static void removeFromRenderQueue(Object* o);

private:
	static bool initOpenGL();
	static void printProgramLog(GLuint program);
	static void printShaderLog(GLuint shader);
	static void MessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);
	static std::string loadShaderCodeFromFilepath(std::string filename);
};

