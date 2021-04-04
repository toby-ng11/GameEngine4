#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
ivec2 MouseEventListener::mouse = ivec2();
ivec2 MouseEventListener::prevMouse = ivec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_)
{
	if (e_.type == SDL_MOUSEBUTTONDOWN) {
		UpdateMousePosition();
		NotifyOfMousePressed(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEBUTTONUP) {
		UpdateMousePosition();
		NotifyOfMouseReleased(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEMOTION) {
		UpdateMousePosition();
		NotifyOfMouseMove();
	}
	else if (e_.type == SDL_MOUSEWHEEL) {
		UpdateMousePosition();
		NotifyOfMouseScroll(e_.wheel.y);
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_)
{
	if (engineInstance) {
		engineInstance->NotifyOfMousePressed(mouse, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_)
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseReleased(mouse, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseMove()
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseMove(mouse);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y_)
{
	if (engineInstance) {
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

ivec2 MouseEventListener::GetPreviousMousePosition()
{
	return prevMouse;
}

ivec2 MouseEventListener::GetMousePosition()
{
	return mouse;
}

ivec2 MouseEventListener::GetMouseOffset()
{
	return ivec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePosition()
{
	int tmpX, tmpY; // mouse pos
	SDL_GetMouseState(&tmpX, &tmpY); // new mouse pos
	tmpY = static_cast<int>(engineInstance->GetScreenHeight()) - tmpY; // top screen to bottom screen
	if (firstUpdate) {
		prevMouse.x = mouse.x = tmpX;
		prevMouse.y = mouse.y = tmpY;
		firstUpdate = false;
	}
	else {
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tmpX;
		mouse.y = tmpY;
	}
}
