#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <sstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <glew.h>
#include "../Core/Debug.h"

using namespace std;

class ShaderHandler
{
public:
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator=(const ShaderHandler&) = delete;
	ShaderHandler& operator=(ShaderHandler&&) = delete;

	// Get Shader Instance
	static ShaderHandler* GetInstance();

	// Create OpenGL program
	void CreateProgram(const string& shaderName_, const string& vertexShaderFileName_, const string& fragmentShaderFileName_);

	// Return the GLuint/ID of this specific Shader
	GLuint GetShader(const string& shaderName_);
	void OnDestroy();

private:
	ShaderHandler();
	~ShaderHandler();

	static unique_ptr<ShaderHandler> shaderInstance; // hold pointer to this shader class
	friend default_delete<ShaderHandler>; // delete unique_ptr by default (destructor)

	// Read actual shader file, return string in that file
	string ReadShader(const string& filePath_);
	//Create Shader obj
	GLuint CreateShader(GLenum shaderType_, const string& source_, const string& shaderName_);

	// Hold all created shader programs 
	// In dictionary : WORD  has     DEFINITION
	//                 KEY   has      VALUE
	//                 STRING has     GLuint
	//                    |           |
	static unordered_map<string, GLuint> programs;

};

#endif // !SHADERHANDLER_H



