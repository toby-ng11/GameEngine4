#include "Timer.h"

Timer::Timer() :prevTicks(0), currentTicks(0)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	prevTicks = currentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks()
{
	prevTicks = currentTicks; // update previous first
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const
{
	return (currentTicks - prevTicks) / MILLI_TO_SEC;
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
	// sleeptime purpose is to maintain the consistence of framerate
	unsigned int milliSecsPerFrame = static_cast<unsigned int>(MILLI_TO_SEC) / fps_;

	if (milliSecsPerFrame == 0) {
		return 0;
	}
	//                                               this one    <   this one
	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currentTicks);
	if (sleepTime > milliSecsPerFrame) {
		return milliSecsPerFrame;
	}
	return sleepTime;
}

float Timer::GetCurrentTickMilli() const
{
	return static_cast<float>(currentTicks); // cast to avoid warning
}

float Timer::GetCurrentTickSec() const
{
	return currentTicks / MILLI_TO_SEC;
}