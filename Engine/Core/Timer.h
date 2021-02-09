#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

// Convert millisecond to second
constexpr float MILLI_TO_SEC = 1000.0f;

class Timer
{
public:

	Timer(const Timer &) = delete;             // ->
	Timer(Timer&&) = delete;                   // ->
	Timer& operator=(const Timer&) = delete;   // ->
	Timer& operator=(Timer&&) = delete;        // Restrict using the copy & move constructor of this class

	Timer();
	~Timer();

	// Init
	void Start();
	// Update frame
	void UpdateFrameTicks();
	// Return deltaTime
	float GetDeltaTime()const;
	// Calculate and return SleepTime
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTickMilli()const;
	float GetCurrentTickSec()const;
private:
	unsigned int prevTicks;
	unsigned int currentTicks;
};

#endif // !TIMER_H



