///////////////////////////////////////////////////////////////
// main.cpp
// 
// Main class for the game engine. This launches the game engine directly, with no 
// map editing functionality. It contains the int main() function and thread 
// functions. The main difference between main.cpp and game.cpp is their relative 
// scopes - main.cpp calls Game while handling high level execution and thread 
// operations, while game.cpp contains the functions called by main.cpp, which have
// more to do with the functionality of the engine itself. 
///////////////////////////////////////////////////////////////


#include <iostream>
#include <SDL.h>
#undef main
#include "game.h"
#include "io/parseCFG.h"
#include "variables.h"
#include <thread>

Game *g = nullptr;
bool ready;

//Updating thread
void t_update()
{
	//g->update();
}

//Rendering thread
void t_render()
{
    //Initialize the renderer ON THIS THREAD. We can only render from the thread 
    //that OpenGL was initialized from, so this is key. 
    g->initRenderer();
    //Signal that we've finished setting up the renderer; we can continue all final 
    //parts of setup now
    ready = true;

    //Render while the game is running
    while (g->running()) {
        g->render();
    }
}

//Unused events handling thread
void t_handleEvents() {
	//g->handleEvents();
}

int main(int argc, const char* argv[]) {
	g = new Game();

	//Parse the config file, in the default path of cfg/config.cfg
	ParseCFG::parseCFG(g);

	//Initialize the game engine. This does a lot of important stuff!!
	g->init("djent", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2, 2, false);

    ready = false;

    std::thread renderThread(t_render);

    //Wait until the renderer is initialized to start all other processes
    while (!ready) {
        
    }

    //Start the game engine
    g->start();

	//Main game loop
	while (g->running())
	{
		g->handleEvents();

		//Start separate threads for rendering and updating
		std::thread updateThread(t_update);

		//Join threads before the loop repeats. We want threads to process at the 
		//same time, but we want them all to stop before we start the next cycle. 
		updateThread.join();
	}

    //Join the rendering thread here
    renderThread.join();

	//Clean everything up
	g->clean();

	return 0;
}













/*
// Headers
#include <SDL.h>
#undef main
#include <GL/glew.h>
#include <SDL_opengl.h>
//#include <SFML/Window.hpp>

// Shader sources
const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    out vec4 outColor;
    void main()
    {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)glsl";

int main(int argc, const char* argv[])
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    int flags = SDL_WINDOW_OPENGL;
    SDL_Window* window = SDL_CreateWindow("a", 100, 100, 800, 600,
        flags);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);



    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {
         0.0f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle from the 3 vertices
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    SDL_GL_DeleteContext(context);

    return 0;
}*/