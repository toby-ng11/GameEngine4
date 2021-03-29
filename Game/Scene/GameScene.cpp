#include "GameScene.h"

GameScene::GameScene() :shape(nullptr), model(nullptr)
{

}

GameScene::~GameScene()
{
	model = nullptr;

	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	cout << "Game Scene" << endl;
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(vec3(0.0f, 0.25f, 4.0f));

	CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(vec3(5.0f, 0.0f, 2.0f), 0.2f, 0.8f, 0.6f, vec3(1.0f, 1.0f, 1.0f)));
	//CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(vec3(-5.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, vec3(1.0f, 1.0f, 1.0f)));

	//TextureHandler::GetInstance()->CreateTexture("CheckerboardTexture", "./Resources/Textures/CheckerboardTexture.png");

	// Load obj and material
	model = new Model("./Resources/Models/hollow knight.obj", "./Resources/Materials/hollow knight.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	//model->SetAngle(model->GetAngle() + 0.005f);
	shape->Update(deltaTime_);
}

void GameScene::Render()
{
	shape->Render(CoreEngine::GetInstance()->GetCamera());
}
