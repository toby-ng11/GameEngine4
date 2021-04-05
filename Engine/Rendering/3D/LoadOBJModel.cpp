#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() :vertices(vector<vec3>()), normals(vector<vec3>()), textureCoords(vector<vec2>()),
indices(vector<unsigned int>()), normalIndices(vector<unsigned int>()), textureIndices(vector<unsigned int>()),
meshVertices(vector<Vertex>()), subMeshes(vector<SubMesh>()), currentMaterial(Material())
{
    vertices.reserve(200);
    normals.reserve(200);
    textureCoords.reserve(200);
    indices.reserve(200);
    normalIndices.reserve(200);
    textureIndices.reserve(200);
    meshVertices.reserve(200);
    subMeshes.reserve(200);
}

LoadOBJModel::~LoadOBJModel()
{
    vertices.clear();
    normals.clear();
    textureCoords.clear();
    indices.clear();
    normalIndices.clear();
    textureIndices.clear();
    meshVertices.clear();
    subMeshes.clear();
}

void LoadOBJModel::LoadModel(const string& objFilePath_, const string& mtlFilePath_)
{
    LoadMaterialLibrary(mtlFilePath_);
    LoadModel(objFilePath_);
}

vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
    return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() const
{
    return boundingBox;
}

void LoadOBJModel::PostProcessing()
{
    for (unsigned int i = 0; i < indices.size(); i++) {
        Vertex vert;
        vert.position = vertices[indices[i]];
        vert.normal = normals[normalIndices[i]];
        vert.textureCoordinates = textureCoords[textureIndices[i]];
        meshVertices.push_back(vert);
    }
    SubMesh mesh;
    mesh.vertexList = meshVertices;
    mesh.meshIndices = indices;
    mesh.material = currentMaterial;

    subMeshes.push_back(mesh);

    indices.clear();
    normalIndices.clear();
    textureIndices.clear();
    meshVertices.clear();

    currentMaterial = Material();
}

void LoadOBJModel::LoadModel(const string& filePath_)
{
    ifstream in(filePath_.c_str(), ios::in);
    if (!in) {
        Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
    }
    string line;

    float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

    while(getline(in, line)) {

        // VERTEX DATA
        if (line.substr(0, 2) == "v ") {
            stringstream v(line.substr(2));
            float x, y, z;
            v >> x >> y >> z;
            vertices.push_back(vec3(x, y, z));

            if (x <= minX) minX = x;
            if (y <= minY) minY = y;
            if (z <= minZ) minZ = z;

            if (x >= maxX) maxX = x;
            if (y >= maxY) maxY = y;
            if (z >= maxZ) maxZ = z;
           
            boundingBox.minVert = vec3(minX, minY, minZ);
            boundingBox.maxVert = vec3(maxX, maxY, maxZ);
        }

        // VERTEX NORMALS
        if (line.substr(0, 2) == "vn") {
            stringstream vn(line.substr(2));
            float x, y, z;
            vn >> x >> y >> z;
            normals.push_back(vec3(x, y, z));
        }

        // TEXTURE COORDS
        if (line.substr(0, 2) == "vt") {
            stringstream vt(line.substr(2));
            float x, y;
            vt >> x >> y;
            textureCoords.push_back(vec2(x, y));
        }
        
        // FACE
        if (line.substr(0, 2) == "f ") {
            stringstream f(line.substr(2));
            unsigned int Index[3], textureIndex[3], normalIndex[3];
            char slash;
            f >> Index[0] >> slash >> textureIndex[0] >> slash >> normalIndex[0]
                >> Index[1] >> slash >> textureIndex[1] >> slash >> normalIndex[1]
                >> Index[2] >> slash >> textureIndex[2] >> slash >> normalIndex[2];
      
            indices.push_back(Index[0] - 1);
            indices.push_back(Index[1] - 1);
            indices.push_back(Index[2] - 1);
            textureIndices.push_back(textureIndex[0] - 1);
            textureIndices.push_back(textureIndex[1] - 1);
            textureIndices.push_back(textureIndex[2] - 1);
            normalIndices.push_back(normalIndex[0] - 1);
            normalIndices.push_back(normalIndex[1] - 1);
            normalIndices.push_back(normalIndex[2] - 1);
        }

        // NEW MESH
        else if (line.substr(0, 7) == "usemtl ") {
            if (indices.size() > 0) {
                PostProcessing();
            }
            LoadMaterial(line.substr(7));
        }
    }
    PostProcessing();
}

void LoadOBJModel::LoadMaterial(const string& matName_)
{
    currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const string& matFilePath_)
{
    MaterialLoader::LoadMaterial(matFilePath_);
}
