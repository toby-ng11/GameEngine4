#ifndef MODEL_H
#define MODEL_H

#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"


class Model
{
public:
	Model(const string& objPath_, const string& matPath_, GLuint shaderProgram_);
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);

	unsigned int CreateInstance(vec3 position_, float angle_, vec3 rotation_, vec3 scale_); // return number of the current/new instance
    void UpdateInstance(unsigned int index_, vec3 position_, float angle_, vec3 rotation_, vec3 scale_);
	
	mat4 GetTransform(unsigned int index_) const;

	GLuint GetShaderProgram() const;

	BoundingBox GetBoundingBox() const;

private:
	vector<Mesh*> meshes; // pass by ptr
	GLuint shaderProgram;
	vector<mat4> modelInstances; // hold vector of all model matricies
	
	LoadOBJModel* obj;

	mat4 CreateTransform(vec3 postion_, float angle_, vec3 rotation_, vec3 scale_) const; // create model matrix
	void LoadModel();

	BoundingBox boundingBox;
	
};

#endif // !MODEL_H



