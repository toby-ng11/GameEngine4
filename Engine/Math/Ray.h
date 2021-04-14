#ifndef RAY_H
#define RAY_H

#include "BoundingBox.h"

struct Ray
{
	vec3 origin;
	vec3 direction;
	float intersectionDist;

	// Emty ray
	inline Ray() {
		origin = vec3();
		direction = vec3();
		intersectionDist = 0.0f;
	}

	// Ray constructor
	inline Ray(vec3 origin_, vec3 direction_) {
		origin = origin_;
		direction = direction_;
		intersectionDist = 0.0f;
	}

	// Ray a = Ray b
	inline Ray& operator=(const Ray& ray_) {
		origin = ray_.origin;
		direction = ray_.direction;
		intersectionDist = 0.0f;
	}

	// Check collision
	inline bool IsColliding(BoundingBox* box_) {
		intersectionDist = -1.0f;
		return true;
	}
};


#endif // !RAY_H


