#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(string filePath_)
{
	ifstream in(filePath_.c_str(), ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	string matName = "";
	string line;
	float f, x, y, z;
	while (getline(in, line)) {
		// Material name (newmtl) -> Diffuse map
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}

		// Material shininess (Ns)
		if (line.substr(0, 3) == "\tNs") {
			stringstream v(line.substr(3));
			v >> f;
			m.shininess = f;
		}

		// Material transparency (d)
		if (line.substr(0, 3) == "\td ") {
			stringstream v(line.substr(3));
			v >> f;
			m.transparency = f;
		}

		// Material ambient (Ka)
		if (line.substr(0, 3) == "\tKa") {
			stringstream v(line.substr(3));
			v >> x >> y >> z;
			m.ambient = vec3(x, y, z);
		}

		// Material diffuse (Kd)
		if (line.substr(0, 3) == "\tKd") {
			stringstream v(line.substr(3));
			v >> x >> y >> z;
			m.diffuse = vec3(x, y, z);
		}

		// Material specular (Ks)
		if (line.substr(0, 3) == "\tKs") {
			stringstream v(line.substr(3));
			v >> x >> y >> z;
			m.specular = vec3(x, y, z);
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}