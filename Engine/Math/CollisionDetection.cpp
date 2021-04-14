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
    mat4 modelMatrix = box_->transform;
    vec3 rayOrigin = ray_->origin;
    vec3 rayDirection = ray_->direction;
    vec3 boxMin = box_->minVert;
    vec3 boxMax = box_->maxVert;

    float tMin = CoreEngine::GetInstance()->GetCamera()->GetNearPlane();
    float tMax = CoreEngine::GetInstance()->GetCamera()->GetFarPlane();

    vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
    vec3 delta = worldPos - rayOrigin;

    // X axis
    vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
    float dotDelta = dot(delta, xAxis);
    float dotDir = dot(rayDirection, xAxis);
    if (fabs(dotDir) > 0.001f) {
        float t1 = (dotDelta + boxMin.x) / dotDir;
        float t2 = (dotDelta + boxMax.x) / dotDir;

        if (t1 > t2) { // swap t1 & t2
            float w = t1;
            t1 = t2;
            t2 = w; // => t1 < t2
        }

        if (t2 < tMax) {
            tMax = t2;
        }

        if (t1 > tMin) {
            tMin = t1;
        }
    }
    else {
        if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f) {
            return false;
        }
    }
    
    // Y axis
    
    // Z axis


    ray_->intersectionDist = tMin;
    return true;
}
