#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

#include <SDL.h>
#include <glm/glm.hpp>

using namespace glm;

class CoreEngine; // forward declaration to get ref

class MouseEventListener
{
public:
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;

	MouseEventListener() = delete;
	~MouseEventListener();

	static void RegisterEngineObject(CoreEngine* engine_);
	static void Update(SDL_Event e_);

	// Notify
	static void NotifyOfMousePressed(int buttonType_);
	static void NotifyOfMouseReleased(int buttonType_);
	static void NotifyOfMouseMove();
	static void NotifyOfMouseScroll(int y_);

	// Getter
	static ivec2 GetPreviousMousePosition();
	static ivec2 GetMousePosition();
	static ivec2 GetMouseOffset();

private:
	static CoreEngine* engineInstance;
	static ivec2 mouse, prevMouse;
	static bool firstUpdate;
	static void UpdateMousePosition();
};


#endif // !MOUSEEVENTLISTENER_H


