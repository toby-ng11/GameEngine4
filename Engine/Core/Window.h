#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>              // include in order SDL.h -> glew.h
#include <SDL_opengl.h>
#include <string>
#include <iostream>

using namespace std;

class Window
{
public:

	//Constructor
	Window();

	// Destructor
	~Window();

	// Create window
	bool OnCreate(string name_, int width_, int height_);

	// Destroy window
	void OnDestroy();

	// Return window width
	int GetWidth() const;

	// Return window height
	int GetHeight() const;

	// Return window pointer
	SDL_Window* GetWindow() const;

private:
	// Set attributes before windows created
	void SetPreAttributes();
	// Set attributes after windows created
	void SetPosAttributes();

	// Window width
	int width;
	// Window height
	int height;
	// Window pointer reference to SDL window
	SDL_Window* window;
	// Communicate by OpenGL and SDL with graphic card
	SDL_GLContext context;
};

#endif // !WINDOW_H
