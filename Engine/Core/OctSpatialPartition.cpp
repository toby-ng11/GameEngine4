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

OctSpatialPartition::OctSpatialPartition(float worldSize_) :root(nullptr), rayIntersectionList(vector<OctNode*>())
{
	root = new OctNode(vec3(-(worldSize_ / 2.0f)), worldSize_, nullptr);
	root->Octify(3); // depth lv 3
	cout << "There are " << root->GetChillCount() << " child nodes." << endl;

	rayIntersectionList.reserve(20);
}

OctSpatialPartition::~OctSpatialPartition()
{
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}

	delete root;
	root = nullptr;
}

void OctSpatialPartition::AddObject(GameObject* obj_)
{
	AddObjectToCell(root, obj_);
}

GameObject* OctSpatialPartition::GetCollision(Ray ray_)
{
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}
	PrepareCollisionQuery(root, ray_);

	GameObject* result = nullptr;
	float shortestDistance = FLT_MAX;
	for (auto cell : rayIntersectionList) { // for each node in list
		for (auto obj : cell->objectList) { // for each game obj
			BoundingBox tmp = obj->GetBoundingBox(); // requires l-value
			if (ray_.IsColliding(&tmp)) {
				if (ray_.intersectionDist < shortestDistance) {
					result = obj;
					shortestDistance = ray_.intersectionDist;
				}
			}
		}
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}

void OctSpatialPartition::AddObjectToCell(OctNode* cell_, GameObject* obj_)
{
	BoundingBox* nodeBound = cell_->GetBoundingBox();
	BoundingBox objBound = obj_->GetBoundingBox();

	// check cell_ is a leaf
	if (cell_->IsLeaf()) {

		// check if obj_.getboundingbox() Intersects with cell_.getboundingbox()
		if (nodeBound->Intersects(&objBound)) {

			// true -> add obj_ to that cell_
			cell_->AddCollisionObject(obj_);

			// print out specific obj_ was added to the cell_ pos
			cout << "Added " << obj_->GetTag() << " to cell: " << to_string(nodeBound->maxVert) << endl; <-
		}
	}
	// if cell_ is not a leaf
	else {
		// create for loop goes through each child of cell_
		for (int i = 0; i < CHILDREN_NUMBER; i++) {

			// call AddObjectToCell on each child
			AddObjectToCell(cell_->GetChild(static_cast<OctChildren>(i)), obj_);
		}
	}
}

void OctSpatialPartition::PrepareCollisionQuery(OctNode* cell_, Ray ray_)
{
	BoundingBox* nodeBound = cell_->GetBoundingBox();

	// check cell_ is a leaf
	if (cell_->IsLeaf()) {

		// check if ray_ isColiiding(cell_.getboundingbox())
		if (ray_.IsColliding(nodeBound)) {

			// true -> add cell_ to rayIntersectionList
			rayIntersectionList.push_back(cell_);
		}
	}
	// if not a leaf node
	else {

		// create for loop goes through each child of cell_
		for (int i = 0; i < CHILDREN_NUMBER; i++) {

			// call PrepareCollisionQuery on each child
			PrepareCollisionQuery(cell_->GetChild(static_cast<OctChildren>(i)), ray_);
		}
	}
}