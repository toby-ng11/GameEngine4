#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0),
modelLoc(0), viewLoc(0), projectionLoc(0),
viewPosLoc(0), lightPosLoc(0), lightAmbientLoc(0), lightDiffuseLoc(0), lightSpecularLoc(0), lightColourLoc(0),
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
	glUniform1f(matDiffuseMapLoc, subMesh.material.diffuseMap);

	glUniform1f(matShininessLoc, subMesh.material.shininess);
	glUniform1f(matTransparencyLoc, subMesh.material.transparency);
	glUniform3f(matAmbientLoc, subMesh.material.ambient.x, subMesh.material.ambient.y, subMesh.material.ambient.z);
	glUniform3f(matDiffuseLoc, subMesh.material.diffuse.x, subMesh.material.diffuse.y, subMesh.material.diffuse.z);
	glUniform3f(matSpecularLoc, subMesh.material.specular.x, subMesh.material.specular.y, subMesh.material.specular.z);

	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniform3fv(viewPosLoc, 1, value_ptr(camera_->GetPosition()));

	vector<LightSource*> newlight = camera_->GetLightList();

	float light_ambient1 = newlight[0]->GetAmbient();
	float light_diff1 = newlight[0]->GetDiffuse();
	float light_spec1 = newlight[0]->GetSpecular();

	glUniform3fv(lightPosLoc, 1, value_ptr(newlight[0]->GetPosition()));
	glUniform1fv(lightAmbientLoc, 1, &light_ambient1);
	glUniform1fv(lightDiffuseLoc, 1, &light_diff1);
	glUniform1fv(lightSpecularLoc, 1, &light_spec1);
	glUniform3fv(lightColourLoc, 1, value_ptr(newlight[0]->GetColour()));

	/* 
	float light_ambient2 = newlight[1]->GetAmbient();
	float light_diff2 = newlight[1]->GetDiffuse();
	float light_spec2 = newlight[1]->GetSpecular();

	glUniform3fv(lightPosLoc, 1, value_ptr(newlight[1]->GetPosition()));
	glUniform1fv(ambientLoc, 1, &light_ambient2);
	glUniform1fv(diffuseLoc, 1, &light_diff2);
	glUniform1fv(specularLoc, 1, &light_spec2);
	glUniform3fv(colourLoc, 1, value_ptr(newlight[1]->GetPosition()));
	*/

    //                 location / number of uniform / tranpose matrix? / ref to matrix
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
	

	// Light
	viewPosLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightSpecularLoc = glGetUniformLocation(shaderProgram, "light.specular");
	lightColourLoc = glGetUniformLocation(shaderProgram, "light.lightColor");
}
