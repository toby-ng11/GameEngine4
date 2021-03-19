#version 450 core

layout (location = 0) in vec3 position;  // same order in mesh.cpp
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 colour;

out vec3 Normal;
out vec2 TexCoords;
out vec3 Colour;
out vec3 FragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    //TexCoords = texCoords;
    TexCoords = vec2(texCoords.x, 1.0 - texCoords.y);
    Colour = colour; // out colour = in colour
    FragPosition = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;

    gl_Position = projection * view * model * vec4(position, 1.0f); 
}