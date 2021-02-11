#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	cout << " Start Scene" << endl;
	CoreEngine::GetInstance()->SetCurrentScene(1);

	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
