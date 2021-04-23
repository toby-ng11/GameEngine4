#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

constexpr auto CHILDREN_NUMBER = 8;

enum class OctChildren { // counter clockwise, front to rear
	OCT_TLF, // top left front
	OCT_BLF, // bottom left front
	OCT_BRF, // bottom right front
	OCT_TRF, // top right front
	OCT_TLR, // top left rear
	OCT_BLR, // bottom left rear
	OCT_BRR, // bottom right rear
	OCT_TRR  // top right rear
};

class OctNode {
public:
	OctNode(vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	
	void Octify(int depth_);

	OctNode* GetParent();
	OctNode* GetChild(OctChildren childPos_);

	void AddCollisionObject(GameObject* obj_); // add obj to node
	int GetObjectCount() const; // get number of objs inside a specific node
	bool IsLeaf() const; // check if node is a leaf or not
	BoundingBox* GetBoundingBox() const; // get bounding box of the node
	int GetChillCount() const; // get number of childs of a specific node
private:
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];
	vector<GameObject*> objectList;
	float size;
	static int childNum;
};

#endif // !OCTSPATIALPARTITION_H


