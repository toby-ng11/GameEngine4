#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

using namespace std;
using namespace glm;

struct Material {

	inline Material() :diffuseMap(0), shininess(32.0f), transparency(1.0f),
		ambient(vec3(1.0f)), diffuse(vec3(1.0f)), specular(vec3(1.0f)),
		name("") {}

	GLuint diffuseMap; // newmtl

	float shininess; // Ns
	float transparency; // d

	vec3 ambient; // Ka
	vec3 diffuse; // Kd
	vec3 specular; // Ks

	string name;
};

class MaterialHandler
{
public:
	MaterialHandler(const MaterialHandler&) = delete;
	MaterialHandler(MaterialHandler&&) = delete;
	MaterialHandler& operator=(const MaterialHandler&) = delete;
	MaterialHandler& operator=(MaterialHandler&&) = delete;

	// Return ref to MaterialHandler
	static MaterialHandler* GetInstance();

	void AddMaterial(Material mat_);
	const Material GetMaterial(const string& matName_) const;
	void OnDestroy();

private:
	MaterialHandler();
	~MaterialHandler();

	static unique_ptr< MaterialHandler> materialInstance;
	friend default_delete< MaterialHandler>;

	static vector<Material> materials;
};

#endif // !MATERIALHANDLER


