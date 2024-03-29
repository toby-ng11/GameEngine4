#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Events/EventListener.h"

#include"../Rendering/SceneGraph.h"
#include "../Rendering/3D/GameObject.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"
#include "../Graphics/MaterialHandler.h"

#include "../Camera/Camera.h"

//class Mesh;

class CoreEngine
{
public:
	// Singleton
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	// Return a reference to this core engine object
	static CoreEngine* GetInstance();

	// Create window
	bool OnCreate(string name_, int width_, int height_);
	void Run();
	void Exit();

	// Getter
	bool GetIsRunning()const;
	int GetCurrentScene() const;
	float GetScreenWidth() const;
	float GetScreenHeight() const;
	Camera* GetCamera() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);
	void SetCamera(Camera* camera_);

	void NotifyOfMousePressed(ivec2 mouse_, int buttonType_);
	void NotifyOfMouseReleased(ivec2 mouse_, int buttonType_);
	void NotifyOfMouseMove(ivec2 mouse_);
	void NotifyOfMouseScroll(int y_);

private:
	CoreEngine();
	~CoreEngine();

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static unique_ptr<CoreEngine> engineInstance; // hold pointer to this engine class
	friend default_delete<CoreEngine>; // delete unique_ptr by default (destructor)

	Window* window;

	bool isRunning;

	Timer* timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;
};

#endif // !COREENGINE_H
