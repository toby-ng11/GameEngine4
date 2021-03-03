#include "Camera.h"
#include "../Core/CoreEngine.h"

Camera::Camera() :position(vec3()), 
fieldOfView(0.0f),
forward(vec3()), up(vec3()), right(vec3()), worldUp(vec3()), 
nearPlane(0.0f), farPlane(0.0f),
yaw(0.0f), pitch(0.0f),
perspective(mat4()), orthographic(mat4()), view(mat4())
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

    UpdateCameraVector();
}

Camera::~Camera()
{
}

void Camera::SetPosition(vec3 position_)
{
    position = position_;
    UpdateCameraVector();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
    yaw = yaw_;
    pitch = pitch_;
    UpdateCameraVector();
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

void Camera::UpdateCameraVector()
{
    forward.x = cos(radians(yaw)) * cos(radians(pitch));
    forward.y = sin(radians(pitch));
    forward.z = sin(radians(yaw)) * cos(radians(pitch));

    forward = normalize(forward);

    right = normalize(cross(forward, worldUp));

    up = normalize(cross(right, forward));
    
    view = lookAt(position, position + forward, up);
}
