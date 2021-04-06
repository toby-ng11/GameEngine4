#include "GameObject.h"

GameObject::GameObject(Model* model_, vec3 position_) :model(nullptr), position(vec3()), angle(0.0f), rotation(vec3(0.0f, 1.0f, 0.0f)), scale(vec3(1.0f)), modelInstance(0)
{
	model = model_;
	position = position_;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance); // get model matrix out of model

		cout << "Min: " << to_string(boundingBox.minVert) << ", Max: " << to_string(boundingBox.maxVert) << endl;
	}
}

GameObject::~GameObject()
{
	model = nullptr;
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 0.005f);
}

void GameObject::Render(Camera* camera_)
{
	if (model) {
		model->Render(camera_);
	}
}

vec3 GameObject::GetPosition() const
{
	return position;
}

float GameObject::GetAngle() const
{
	return angle;
}

vec3 GameObject::GetRoation() const
{
	return rotation;
}

vec3 GameObject::GetScale() const
{
	return scale;
}

string GameObject::GetTag() const
{
	return tag;
}

BoundingBox GameObject::GetBoundingBox() const
{
	return boundingBox;
}

void GameObject::SetPosition(vec3 position_)
{
	position = position_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(vec3 rotation_)
{
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(vec3 scale_)
{
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
		boundingBox.minVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
		boundingBox.maxVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
	}
}

void GameObject::SetTag(string tag_)
{
	tag = tag_;
}