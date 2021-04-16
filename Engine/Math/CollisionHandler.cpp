#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
vector<GameObject*> CollisionHandler::prevCollisions = vector<GameObject*>();
vector<GameObject*> CollisionHandler::colliders = vector<GameObject*>();

CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnCreate()
{
	colliders.clear();
	prevCollisions.clear();
}

void CollisionHandler::AddObject(GameObject* go_)
{
	colliders.push_back(go_);
}

void CollisionHandler::MouseUpdate(vec2 mousePosition_, int buttonType_)
{
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePosition_,
		CoreEngine::GetInstance()->GetScreenWidth(), 
		CoreEngine::GetInstance()->GetScreenHeight(),
		CoreEngine::GetInstance()->GetCamera());

	GameObject* hitResult = nullptr;
	float shortestDistance = FLT_MAX;

	for (auto g : colliders) {
		BoundingBox tmp = g->GetBoundingBox(); // little confuse here (if &g -> & requires I-value)
		if (mouseRay.IsColliding(&tmp)) {
			if (mouseRay.intersectionDist < shortestDistance) {
				hitResult = g;
				shortestDistance = mouseRay.intersectionDist;
			}
		}
	}

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

void CollisionHandler::OnDestroy()
{
	for (auto entry : colliders) {
		entry = nullptr;
	}
	colliders.clear();

	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();
}

CollisionHandler::CollisionHandler()
{
	colliders.reserve(10);
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}
