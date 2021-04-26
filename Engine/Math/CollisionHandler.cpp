#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
vector<GameObject*> CollisionHandler::prevCollisions = vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_)
{
	prevCollisions.clear();
	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* go_)
{
	if (scenePartition != nullptr) {
		scenePartition->AddObject(go_);
	}
}

void CollisionHandler::MouseUpdate(vec2 mousePosition_, int buttonType_)
{
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePosition_,
		CoreEngine::GetInstance()->GetScreenWidth(), 
		CoreEngine::GetInstance()->GetScreenHeight(),
		CoreEngine::GetInstance()->GetCamera());

	if (scenePartition != nullptr) {
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);

		if (hitResult) {
			hitResult->SetHit(true, buttonType_);
		}

		for (auto c : prevCollisions) {
			if (hitResult != c && c != nullptr) {
				c->SetHit(false, buttonType_);
			}
		}
		prevCollisions.clear();

		if (hitResult) {
			prevCollisions.push_back(hitResult);
		}
	}
}

void CollisionHandler::OnDestroy()
{
	delete scenePartition;
	scenePartition = nullptr;

	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();
}

CollisionHandler::CollisionHandler()
{
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}
