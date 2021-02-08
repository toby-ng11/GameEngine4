#include "CoreEngine.h"

unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() :window(nullptr), isRunning(false), fps(60) {}

CoreEngine::~CoreEngine()
{
}

CoreEngine* CoreEngine::GetInstance()
{
	// check if engineInstance is null
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();

}

bool CoreEngine::OnCreate(string name_, int width_, int height_)
{
	window = new Window(); // intialize window ptr
	// check if Window creation is ok
	if (!window->OnCreate(name_, width_, height_)) {
		cout << "Window failed to initialize" << endl;
		OnDestroy();
		return isRunning = false;
	}
	timer.Start();
	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning) {
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

		OnDestroy();
	
}

bool CoreEngine::GetIsRunning()
{
	return isRunning;
}

void CoreEngine::Update(const float deltaTime_)
{
	cout << deltaTime_ << endl;
}

void CoreEngine::Render()
{
	//set screen to this color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// clear color and depth bufffer bit
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// call game render
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}
