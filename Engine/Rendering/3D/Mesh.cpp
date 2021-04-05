#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0),
modelLoc(0), viewLoc(0), projectionLoc(0),
viewPosLoc(0), lightPosLoc(), lightAmbientLoc(), lightDiffuseLoc(), lightSpecularLoc(), lightColourLoc(),
matDiffuseMapLoc(0), matShininessLoc(0), matTransparencyLoc(0), matAmbientLoc(0), matDiffuseLoc(0), matSpecularLoc(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	subMesh.vertexList.clear();
	subMesh.meshIndices.clear();
}

void Mesh::Render(Camera* camera_, vector<mat4>& instances_)
{
	// Material
	glUniform1uiv(matDiffuseMapLoc, 1, &subMesh.material.diffuseMap);
	glUniform1fv(matShininessLoc, 1, &subMesh.material.shininess);
	glUniform1fv(matTransparencyLoc,1, &subMesh.material.transparency);
	glUniform3fv(matAmbientLoc, 1, value_ptr(subMesh.material.ambient));
	glUniform3fv(matDiffuseLoc, 1, value_ptr(subMesh.material.diffuse));
	glUniform3fv(matSpecularLoc, 1, value_ptr(subMesh.material.specular));

	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	// Camera
	glUniform3fv(viewPosLoc, 1, value_ptr(camera_->GetPosition()));

	// Light
	for (unsigned int i = 0; i < camera_->GetLightList().size(); i++) {
		string lightIndex = "light[" + to_string(i) + "]";

		lightPosLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".lightPos").c_str());
		lightAmbientLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".ambient").c_str());
		lightDiffuseLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".diffuse").c_str());
		lightSpecularLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".specular").c_str());
		lightColourLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".lightColor").c_str());

		glUniform3fv(lightPosLoc, 1, value_ptr(camera_->GetLightList()[i]->GetPosition()));
		glUniform1f(lightAmbientLoc, camera_->GetLightList()[i]->GetAmbient());
		glUniform1f(lightDiffuseLoc, camera_->GetLightList()[i]->GetDiffuse());
		glUniform1f(lightSpecularLoc, camera_->GetLightList()[0]->GetSpecular());
		glUniform3fv(lightColourLoc, 1, value_ptr(camera_->GetLightList()[i]->GetColour()));
	}

	// Model
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(camera_->GetPerspective()));

	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST); // take Z value of objects into account

	for (unsigned int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	// setting uniform before drawing arrays
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO); // create VAO
	glGenBuffers(1, &VBO); // create VBO
	glBindVertexArray(VAO); // bind VAO to GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind VBO to GPU as buffer
	//            buffer type   / size of array = vector size*byte size of each vertex element                      
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0); // fisrt
	//                   lcation / size of vertex (vec3) / <-3 float values / normalize? /space between vertecies, 
	glVertexAttribPointer(  0,             3,               GL_FLOAT,       GL_FALSE,      sizeof(Vertex),       (GLvoid*)0);
	
	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	// Get location from the beginning

	// Model
	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	// Material
	matDiffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	matShininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	matTransparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	matAmbientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	matDiffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	matSpecularLoc = glGetUniformLocation(shaderProgram, "material.specular");
	
	// Camera
	viewPosLoc = glGetUniformLocation(shaderProgram, "viewPosition");

	// Light
	/*
	for (unsigned int i = 0; i < CoreEngine::GetInstance()->GetCamera()->GetLightList().size(); i++) {

		string lightIndex = "light[" + to_string(i) + "]";

		lightPosLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".lightPos").c_str());
		lightAmbientLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".ambient").c_str());
		lightDiffuseLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".diffuse").c_str());
		lightSpecularLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".specular").c_str());
		lightColourLoc = glGetUniformLocation(shaderProgram, (lightIndex + ".lightColor").c_str());
    }
	*/
}
