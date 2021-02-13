#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

class Model
{
public:
	Model();
	~Model();

	void Render();
	void AddMesh(Mesh* mesh_);

private:
	vector<Mesh*> meshes; // pass by ptr
};

#endif // !MODEL_H



