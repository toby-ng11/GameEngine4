#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	glm::vec3 colour;
};
class Mesh
{
public:

	// Constructor
	Mesh(vector<Vertex>& vertexList_); // passing by ref
	~Mesh();

	void Render();

private:
	void GenerateBuffers();
	GLuint VAO, VBO; // VAO = Vertex Array Object, VBO = Vertex Buffer Object
	vector<Vertex> vertexList;
};

#endif // !MESH_H



