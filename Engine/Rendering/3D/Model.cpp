#include "Model.h"

Model::Model(GLuint shaderProgram_, vec3 position_, float angle_, vec3 rotation_, vec3 scale_) :
	meshes(vector<Mesh*>()), shaderProgram(0), position(vec3()), angle(0.0f), rotation(vec3(0.0f, 1.0f, 0.0f)), scale(vec3(1.0f))
{
	shaderProgram = shaderProgram_;

	position = position_;
	angle = angle_;
	rotation = rotation_;
	scale = scale_;
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
		m->Render(GetTransform());
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	meshes.push_back(mesh_);

}

vec3 Model::GetPosition() const
{
	return position;
}

float Model::GetAngle() const
{
	return angle;
}

vec3 Model::GetRoation() const
{
	return rotation;
}

vec3 Model::GetScale() const
{
	return scale;
}

void Model::SetPosition(vec3 position_)
{
	position = position_;
}

void Model::SetAngle(float angle_)
{
	angle = angle_;
}

void Model::SetRotation(vec3 rotation_)
{
	rotation = rotation_;
}

void Model::SetScale(vec3 scale_)
{
	scale = scale_;
}

mat4 Model::GetTransform() const
{
	mat4 model;
	model = translate(model, position);
	model = rotate(model, angle, rotation);
	model = glm::scale(model, scale); // duplicate "scale", must use scope
	return model;
}
