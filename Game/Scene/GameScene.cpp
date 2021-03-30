#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	
}

bool GameScene::OnCreate()
{
	cout << "Game Scene" << endl;
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(vec3(0.0f, 0.25f, 4.0f));

	CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(vec3(0.0f, 0.0f, 2.0f), 0.2f, 0.8f, 0.6f, vec3(1.0f, 1.0f, 1.0f)));
	//CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(vec3(-5.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, vec3(1.0f, 1.0f, 1.0f)));

	Model* diceModel = new Model("Resources/Models/Dice.obj", "/Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* appleModel = new Model("Resources/Models/Apple.obj", "/Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(appleModel);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, vec3(-2.0f, 0.0f, -2.0f)));
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, vec3(1.5f, 0.0f, 0.0f)), "Apple"); // "Apple" means tag

	diceModel = nullptr;
	appleModel = nullptr;


	return true;
}

void GameScene::Update(const float deltaTime_)
{
	//model->SetAngle(model->GetAngle() + 0.005f);
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}
