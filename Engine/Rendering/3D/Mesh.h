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
class Mesh
{
public:

	// Constructor
	Mesh(vector<Vertex>& vertexList_,GLuint textureID_, GLuint shaderProgram_); // passing by ref
	~Mesh();

	void Render(Camera* camera_, mat4 transform_);

private:
	void GenerateBuffers();
	GLuint VAO, VBO; // VAO = Vertex Array Object, VBO = Vertex Buffer Object
	vector<Vertex> vertexList;
	GLuint shaderProgram;
	GLuint textureID;
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc;

	GLuint viewPos, lightPosLoc, ambientLoc, diffuseLoc, specularLoc, colourLoc;
};

#endif // !MESH_H



