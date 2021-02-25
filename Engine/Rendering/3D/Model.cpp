#include "Model.h"

Model::Model(GLuint shaderProgram_) :meshes(vector<Mesh*>()), shaderProgram(0)
{
	shaderProgram = shaderProgram_;
}

Model::~Model()
{
	if (meshes.size() > 0) {
		// colon means "in"
		for (auto m : meshes) {
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}
}

void Model::Render()
{
	glUseProgram(shaderProgram); 
	for (auto m : meshes) {
		m->Render();
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	meshes.push_back(mesh_);

}
