#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/CoreEngine.h"

CollisionDetection::~CollisionDetection()
{
}

Ray CollisionDetection::MousePosToWorldRay(vec2 mouseCoords_, float screenWidth_, float sreenHeight_, Camera* camera_)
{
    // Ray start point
    vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / sreenHeight_ - 0.5f) * 2.0f, -1.0f, 1.0f); // in NDC space, z start at -1.0
    // Ray end pos
    vec4 rayEndNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / sreenHeight_ - 0.5f) * 2.0f, 0.0f, 1.0f);

    mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

    vec4 rayStartWorld = inverse * rayStartNDC;
    rayStartWorld /= rayStartWorld.w; // normalizing

    vec4 rayEndWorld = inverse * rayEndNDC;
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

    float w = 0.0f;

    // X axis
    vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
    float dotDelta = dot(delta, xAxis);
    float dotDir = dot(rayDirection, xAxis);
    if (fabs(dotDir) > 0.001f) { // for not dividing by 0
        float t1 = (dotDelta + boxMin.x) / dotDir; // intersection with left plane
        float t2 = (dotDelta + boxMax.x) / dotDir; // intersection with right plane

        if (t1 > t2) { // swap t1 & t2
            w = t1;
            t1 = t2;
            t2 = w; // => t1 < t2
        }

        if (t2 < tMax) {
            tMax = t2;
        }

        if (t1 > tMin) {
            tMin = t1;
        }
        
        if (tMax < tMin) {
            return false;
        }
    }
    else {
        if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f) {
            return false;
        }
    }
    
    // Y axis
    vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
    dotDelta = dot(delta, yAxis);
    dotDir = dot(rayDirection, yAxis);
    if (fabs(dotDir) > 0.001f) {
        float t1 = (dotDelta + boxMin.y) / dotDir;
        float t2 = (dotDelta + boxMax.y) / dotDir;

        if (t1 > t2) {
            w = t1;
            t1 = t2;
            t2 = w; 
        }

        if (t2 < tMax) {
            tMax = t2;
        }

        if (t1 > tMin) {
            tMin = t1;
        }

        if (tMax < tMin) {
            return false;
        }
    }
    else {
        if (-dotDelta + boxMin.y > 0.0f || -dotDelta + boxMax.y < 0.0f) {
            return false;
        }
    }
   
    // Z axis
    vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
    dotDelta = dot(delta, zAxis);
    dotDir = dot(rayDirection, zAxis);
    if (fabs(dotDir) > 0.001f) {
        float t1 = (dotDelta + boxMin.z) / dotDir;
        float t2 = (dotDelta + boxMax.z) / dotDir;

        if (t1 > t2) {
            w = t1;
            t1 = t2;
            t2 = w;
        }

        if (t2 < tMax) {
            tMax = t2;
        }

        if (t1 > tMin) {
            tMin = t1;
        }

        if (tMax < tMin) {
            return false;
        }
    }
    else {
        if (-dotDelta + boxMin.z > 0.0f || -dotDelta + boxMax.z < 0.0f) {
            return false;
        }
    }

    ray_->intersectionDist = tMin;
    return true;
}
