#include "Window.h"

Window::Window() :window(nullptr), context(nullptr), height(0), width(0) {}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(string name_, int width_, int height_)
{
	// check if SDL initialization is ok
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Failed to initialize SDL" << endl;
		return false;
	}
	this->width = width_;
	this->height = height_;

	SetPreAttributes();

	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	// check if Window creation is ok
	if (!window) {
		cout << "Failed to create window" << endl;
		return false;
	}

	context = SDL_GL_CreateContext(window); // use SDL
	SetPosAttributes();

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cout << "Failed to initialize GLEW" << endl;
		return false;
	}

	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	// transform clip space -> screen space
	glViewport(0, 0, width, height);

	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // set mask to core profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // version 4
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5); //          .5
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1); // set swap interval = vertical retrace of screen
	glewExperimental = GL_TRUE; // allow checking error of exprimental GPU extensions
}

void Window::SetPosAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32); // depth buff size = 32bit
}