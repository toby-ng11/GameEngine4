#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"

using namespace std;
using namespace glm;

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 textureCoordinates;
	vec3 colour;
};

struct SubMesh {
	vector<Vertex> vertexList;
	vector<unsigned int> meshIndices;
	GLuint textureID = 0;
};

class Mesh
{
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_); // pass SubMesh by ref
	~Mesh();

	void Render(Camera* camera_, vector<mat4>& instances_);

private:
	void GenerateBuffers();
	GLuint VAO, VBO; // VAO = Vertex Array Object, VBO = Vertex Buffer Object
	GLuint shaderProgram;
	
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc; // camera

	GLuint viewPosLoc, lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightSpecularLoc, lightColourLoc; // light

	SubMesh subMesh;
};

#endif // !MESH_H



