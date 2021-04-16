#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::OnCreate()
{
	cout << "You are in Game Scene" << endl;
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(vec3(0.0f, 0.25f, 6.0f));

	CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(vec3(10.0f, 0.0f, 0.0f), 0.1f, 0.5f, 0.5f, vec3(1.0f, 0.0f, 0.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(vec3(-10.0f, 0.0f, 0.0f), 0.1f, 0.5f, 0.5f, vec3(0.0f, 0.0f, 1.0f)));
	CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate();

	Model* diceModel = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* appleModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	Model* hollowknight = new Model("Resources/Models/hollow knight.obj", "Resources/Materials/hollow knight.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(appleModel);
	SceneGraph::GetInstance()->AddModel(hollowknight);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, vec3(-3.5f, 0.0f, -2.0f)));
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, vec3(2.5f, 0.0f, 0.0f)), "Apple"); // "Apple" means tag
	SceneGraph::GetInstance()->AddGameObject(new GameObject(hollowknight, vec3(0.0f, 0.0f, -1.0f)), "hollow knight");

	//diceModel = nullptr;
	appleModel = nullptr;
	hollowknight = nullptr;

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