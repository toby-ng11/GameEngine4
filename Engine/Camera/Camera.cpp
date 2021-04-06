#include "Camera.h"
#include "../Core/CoreEngine.h"

Camera::Camera() :position(vec3()),
fieldOfView(0.0f),
forward(vec3()), up(vec3()), right(vec3()), worldUp(vec3()),
nearPlane(0.0f), farPlane(0.0f),
yaw(0.0f), pitch(0.0f),
perspective(mat4()), orthographic(mat4()), view(mat4()), lightList(vector<LightSource*>())
{
	fieldOfView = 45.0f;
	forward = vec3(0.0f, 0.0f, -1.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetScreenWidth() / CoreEngine::GetInstance()->GetScreenHeight(), nearPlane, farPlane);

	orthographic = ortho(0.0f, CoreEngine::GetInstance()->GetScreenWidth(), 0.0f, CoreEngine::GetInstance()->GetScreenHeight(), -1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera()
{
	lightList.clear();
}

void Camera::SetPosition(vec3 position_)
{
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

mat4 Camera::GetView() const
{
	return view;
}

mat4 Camera::GetPerspective() const
{
	return perspective;
}

mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::AddLight(LightSource* light_)
{
	lightList.push_back(light_);
}

vector<LightSource*> Camera::GetLightList()
{
	return lightList;
}

void Camera::ProcessMouseMovement(vec2 offset_)
{
	offset_ *= 0.05f; // mouse sensitivity

	yaw += offset_.x;
	pitch += offset_.y;

	// 90 < pitch < 90
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	// 0 <= yaw <= 360
	if (yaw < 0.0f) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	UpdateCameraVectors();
}

void Camera::ProcessMouseZoom(int y_)
{
	if (y_ < 0 || y_ > 0) { // y != 0
		position += static_cast<float>(y_) * (forward * 2.0f); // 2.0f means zoom sensitivity
	}
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	forward.x = cos(radians(yaw)) * cos(radians(pitch));
	forward.y = sin(radians(pitch));
	forward.z = sin(radians(yaw)) * cos(radians(pitch));

	forward = normalize(forward);

	right = normalize(cross(forward, worldUp));

	up = normalize(cross(right, forward));

	view = lookAt(position, position + forward, up);
}