#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/CoreEngine.h"

CollisionDetection::~CollisionDetection()
{
}

Ray CollisionDetection::MousePosToWorldRay(vec2 mouseCoords_, vec2 screenSize_, Camera* camera_)
{
    // Ray start point
    vec4 rayStartNDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, -1.0f, 1.0f); // in NDC space, z start at -1.0
    // Ray end pos
    vec4 rayEndNDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, 0.0f, 1.0f);

    mat4 Inverse = inverse(camera_->GetPerspective() * camera_->GetView());

    vec4 rayStartWorld = Inverse * rayStartNDC;
    rayStartWorld /= rayStartWorld.w; // normalizing

    vec4 rayEndWorld = Inverse * rayEndNDC;
    rayEndWorld /= rayEndWorld.w;

    vec3 rayDirWorld(rayEndWorld - rayStartWorld);
    rayDirWorld = normalize(rayDirWorld);

    return Ray(vec3(rayStartWorld), rayDirWorld); // origin point and direction
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_)
{
    return false;
}
