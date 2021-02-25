#include "ShaderHandler.h"

unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;
unordered_map<string, GLuint> ShaderHandler::programs = unordered_map<string, GLuint>();

ShaderHandler* ShaderHandler::GetInstance()
{
	if (shaderInstance.get() == nullptr) {
		shaderInstance.reset(new ShaderHandler);
	}
	return shaderInstance.get();
}

void ShaderHandler::CreateProgram(const string& shaderName_, const string& vertexShaderFileName_, const string& fragmentShaderFileName_)
{
	string vertexShaderCode = ReadShader(vertexShaderFileName_);
	string fragmentShaderCode = ReadShader(fragmentShaderFileName_);

	if (vertexShaderCode == "" || fragmentShaderCode == "") {
		return; // stop void func
	}

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, shaderName_);

	if (vertexShader == 0 || fragmentShader == 0) {
		return;
	}
	
	// Create shader program
	GLint linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader); // attach vertex Shader to program
	glAttachShader(program, fragmentShader); //      fragment

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	if (!linkResult) {
		GLint infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		string programString(programLog.begin(), programLog.end());
		Debug::Error("Failed to link shader " + shaderName_ + ". Error: " + programString, "ShaderHandler.cpp", __LINE__);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(program);
		return;
	}

	// Create a new entry into program's unordered map
	programs[shaderName_] = program; // create new entry, key = shaderName_, value = program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint ShaderHandler::GetShader(const string& shaderName_)
{
	if (programs.find(shaderName_) != programs.end()) { //look throught the unorder_map, return the value of that shader name(key)
		return programs[shaderName_];
	}
	return 0;
}

void ShaderHandler::OnDestroy()
{
	if (programs.size() > 0) {
		for (auto p : programs) {
			glDeleteProgram(p.second); // .second -> VALUE, .first ->key
		}
		programs.clear();
	}
}

ShaderHandler::ShaderHandler()
{
}

ShaderHandler::~ShaderHandler()
{
	OnDestroy();
}

string ShaderHandler::ReadShader(const string& filePath_)
{
	string shaderCode = "";
	ifstream file; // used to read the file
	file.exceptions(ifstream::badbit);
	try {
		file.open(filePath_);
		stringstream tmpStream;
		tmpStream << file.rdbuf(); // >pass to stringstream
		file.close();
		shaderCode = tmpStream.str(); // pass to shadercode
	}
	catch (ifstream::failure error_) {
		Debug::Error("Could not read the shader: " + filePath_, "ShaderHandler.cpp", __LINE__);
		return "";
	}
	return shaderCode;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType_, const string& source_, const string& shaderName_)
{
	GLint compileResult = 0;
	GLuint shader = glCreateShader(shaderType_); // create shader
	const char* shaderCodePtr = source_.c_str(); // convert string into char* obj
	const int shaderCodeSize = source_.size(); // get the size

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize); // pass in source for shader
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (!compileResult) {
		GLint infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		string shaderString(shaderLog.begin(), shaderLog.end());
		Debug::Error("Error compiling shader " + shaderName_ + ". Error: \n" + shaderString, "ShaderHandler.cpp", __LINE__);
		return 0;


	}
	return shader;
}
