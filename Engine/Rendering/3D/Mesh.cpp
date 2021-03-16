#include "Mesh.h"

//                                                                    emty vector
Mesh::Mesh(vector<Vertex>& vertexList_,GLuint textureID_, GLuint shaderProgram_) : VAO(0), VBO(0), vertexList(vector<Vertex>()), shaderProgram(0), textureID(0),
modelLoc(0), viewLoc(0), projectionLoc(0), textureLoc(0)
{
	vertexList = vertexList_;
	textureID = textureID_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	vertexList.clear();
}

void Mesh::Render(Camera* camera_, mat4 transform_)
{
	// use texture0 (unit number of 0)
	glUniform1i(textureLoc, 0); // assign uniform var to texture0
	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBindVertexArray(VAO);
	
	glEnable(GL_DEPTH_TEST); // take Z value of objects into account

    //                 location / number of uniform / tranpose matrix? / ref to matrix
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(transform_));;
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(camera_->GetPerspective()));

	glUniform3fv(viewPos, 1, value_ptr(camera_->GetPosition()));

	vector<LightSource*> newlight = camera_->GetLightList();

	vec3 light_pos = newlight[0]->GetPosition();
	float light_ambient = newlight[0]->GetAmbient();
	float light_diff = newlight[0]->GetDiffuse();
	float light_spec = newlight[0]->GetSpecular();
	vec3 light_color = newlight[0]->GetColour();
	
	glUniform3fv(lightPosLoc, 1, value_ptr(light_pos));
	glUniform1fv(ambientLoc, 1, &light_ambient);
	glUniform1fv(diffuseLoc, 1, &light_diff);
	glUniform1fv(specularLoc, 1, &light_spec);
	glUniform3fv(colourLoc, 1, value_ptr(light_color));

	// setting uniform before draw arrays
	
	glDrawArrays(GL_TRIANGLES, 0, vertexList.size());
	
	glBindVertexArray(0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO); // create VAO
	glGenBuffers(1, &VBO); // create VBO
	glBindVertexArray(VAO); // bind VAO to GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind VBO to GPU as buffer
	//            buffer type   / size of array = vector size*byte size of each vertex element                      
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

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

	//COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Get location from the beginning
	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	// Light
	viewPos = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	ambientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	specularLoc = glGetUniformLocation(shaderProgram, "light.specular");
	colourLoc = glGetUniformLocation(shaderProgram, "light.lightColor");
}
