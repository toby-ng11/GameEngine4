#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject
{
public:
	GameObject(Model* model_);
	~GameObject();

	void Render();
private:
	Model* model;
};

#endif // !GAMEOBJECT_H



