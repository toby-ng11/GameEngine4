#include "OctSpatialPartition.h"

int OctNode::childNum = 0;

OctNode::OctNode(vec3 position_, float size_, OctNode* parent_) :octBounds(nullptr), parent(nullptr), children(), objectList(vector<GameObject*>())
{
	objectList.reserve(10);

	octBounds = new BoundingBox();
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + glm::vec3(size_);

	size = size_;

	parent = parent_;

	for (int i = 0; i < CHILDREN_NUMBER; i++) {
		children[i] = nullptr;
	}
}

OctNode::~OctNode()
{
	delete octBounds;
	octBounds = nullptr;

	if (objectList.size() > 0) { // delete every obj
		for (auto obj : objectList) {
			obj = nullptr;
		}
		objectList.clear();
	}

	for (int i = 0; i < CHILDREN_NUMBER; i++) { // delete every children
		if (children[i] != nullptr) {
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth_)
{
	if (depth_ > 0 && this) {
		float half = size / 2.0f;
		children[static_cast<int>(OctChildren::OCT_TLF)] = new OctNode(vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);        // x        // y + half // z + half
		children[static_cast<int>(OctChildren::OCT_BLF)] = new OctNode(vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z + half), half, this);               // x        // y        // z + half
		children[static_cast<int>(OctChildren::OCT_BRF)] = new OctNode(vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z + half), half, this);        // x + half // y        // z + half
		children[static_cast<int>(OctChildren::OCT_TRF)] = new OctNode(vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this); // x + half // y + half // z + half
		children[static_cast<int>(OctChildren::OCT_TLR)] = new OctNode(vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z), half, this);               // x        // y + half // z
		children[static_cast<int>(OctChildren::OCT_BLR)] = new OctNode(vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z), half, this);                      // x        // y        // z
		children[static_cast<int>(OctChildren::OCT_BRR)] = new OctNode(vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z), half, this);               // x + half // y        // z
		children[static_cast<int>(OctChildren::OCT_TRR)] = new OctNode(vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z), half, this);        // x + half // y + half // z
		childNum += 8;
	}

	if (depth_ > 0 && this) {
		for (int i = 0; i < CHILDREN_NUMBER; i++) {
			children[i]->Octify(depth_ - 1);
		}
	}
}

OctNode* OctNode::GetParent()
{
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPos_)
{
	return children[static_cast<int>(childPos_)];
}

void OctNode::AddCollisionObject(GameObject* obj_)
{
	objectList.push_back(obj_);
}

int OctNode::GetObjectCount() const
{
	return objectList.size();
}

bool OctNode::IsLeaf() const
{
	if (children[0] == nullptr) {
		return true;
	}
	return false;
}

BoundingBox* OctNode::GetBoundingBox() const
{
	return octBounds;
}

int OctNode::GetChillCount() const
{
	return childNum;
}