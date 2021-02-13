#include "Model.h"

Model::Model() :meshes(vector<Mesh*>())
{
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
	for (auto m : meshes) {
		m->Render();
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	meshes.push_back(mesh_);

}
