#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

class Model
{
public:
	Model(GLuint shaderProgram_);
	~Model();

	void Render();
	void AddMesh(Mesh* mesh_);

private:
	vector<Mesh*> meshes; // pass by ptr
	GLuint shaderProgram;
};

#endif // !MODEL_H



