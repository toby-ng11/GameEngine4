#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include <sstream>
#include "Mesh.h"
#include "../../Graphics/TextureHandler.h"

class LoadOBJModel
{
public:
	LoadOBJModel();
	~LoadOBJModel();

	void LoadModel(const string& objFilePath_, const string& mtlFilePath_);
	vector<SubMesh> GetSubMeshes();

private:
	void PostProcessing(); // get all data from obj into submesh obj
	void LoadModel(const string& filePath_);
	void LoadMaterial(const string& matName_);
	void LoadMaterialLibrary(const string& matFilePath_);

	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec2> textureCoords;
	vector<unsigned int> indices, normalIndices, textureIndices;
	vector<Vertex> meshVertices;
	vector<SubMesh> subMeshes;
	GLuint currentTexture;

};
#endif // !LOADOBJMODEL_H



