#include "CoreEngine.h"

unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() :window(nullptr), isRunning(false), fps(60), timer(nullptr), gameInterface(nullptr), currentSceneNum(0), camera(nullptr) {}

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
	Debug::OnCreate();
	window = new Window(); // intialize window ptr
	// check if Window creation is ok
	if (!window->OnCreate(name_, width_, height_)) {
		cout << "Window failed to initialize" << endl;
		OnDestroy();
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl",
		"Engine/Shaders/ColourFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("basicShader",
		"Engine/Shaders/VertexShader.glsl",
		"Engine/Shaders/FragmentShader.glsl");

	if (gameInterface) { 
		if (!gameInterface->OnCreate()) {
			cout << "Game failed to initialize" << endl;
			OnDestroy();
			return isRunning = false;
		}
	}

	//                            full file path
	Debug::Info("Everything worked", __FILE__, __LINE__); // dynamic macro
	timer = new Timer();
	timer->Start();
	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning) {
		timer->UpdateFrameTicks();
		EventListener::Update();
		Update(timer->GetDeltaTime());
		Render();
		SDL_Delay(timer->GetSleepTime(fps));
	}
	OnDestroy();
}

void CoreEngine::Exit()
{
	isRunning = false;
}

bool CoreEngine::GetIsRunning() const
{
	return isRunning;
}

int CoreEngine::GetCurrentScene() const
{
	return currentSceneNum;
}

float CoreEngine::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

float CoreEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

Camera* CoreEngine::GetCamera() const
{
	return camera;
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void CoreEngine::NotifyOfMousePressed(ivec2 mouse_, int buttonType_)
{
}

void CoreEngine::NotifyOfMouseReleased(ivec2 mouse_, int buttonType_)
{
}

void CoreEngine::NotifyOfMouseMove(ivec2 mouse_)
{
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_)
{
	if (camera) {
		camera->ProcessMouseZoom(y_);
	}
}

void CoreEngine::Update(const float deltaTime_)
{
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
		// << deltaTime_ << endl;
	}
	
}

void CoreEngine::Render()
{
	//set screen to this color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// clear color and depth bufffer bit
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// call game render
	if (gameInterface) {
		gameInterface->Render();
	}
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();

	delete gameInterface;
	gameInterface = nullptr;

	delete camera;
	camera = nullptr;

	delete window;
	window = nullptr;

	delete timer;
	timer = nullptr;

	SDL_Quit();
	exit(0);
}
