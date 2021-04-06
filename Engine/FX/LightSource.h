#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class LightSource
{
private:
	vec3 position;
	float ambient, diffuse, specular;
	vec3 colour;

public:

	LightSource(vec3 position_, float ambient_, float diffuse_, float specular_, vec3 colour_);
	~LightSource();

	// Setters
	void SetPosition(vec3 position_);
	void SetAmbient(float ambient_);
	void SetDiffuse(float diffuse_);
	void SetSpecular(float specular_);
	void SetColour(vec3 colour_);

	// Getter
	vec3 GetPosition() const;
	float GetAmbient() const;
	float GetDiffuse() const;
	float GetSpecular()const;
	vec3 GetColour() const;
};

#endif // !LIGHTSOURCE_H
