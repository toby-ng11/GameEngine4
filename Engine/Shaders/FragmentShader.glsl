#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

struct Light {
	vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	vec3 lightColor;
};

struct Material {
	sampler2D diffuseMap;
	float shininess; // Ns
	float transparency; // d
    vec3 ambient; // Ka
	vec3 diffuse; // Kd
	vec3 specular; // Ks
};

uniform vec3 viewPosition;
uniform Material material;
uniform Light light[2];

out vec4 fColour;

void main() {

    vec3 result;

    for (int i = 0; i < 2; i++) {
	  // Ambient
      vec3 ambient = light[i].ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light[i].lightColor;

	  //Diffuse
	  vec3 norm = normalize(Normal);
      vec3 lightDir = normalize(light[i].lightPos - FragPosition);
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light[i].lightColor;

	  // Specular
	  vec3 viewDir = normalize(viewPosition - FragPosition);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
      vec3 specular = (spec * material.specular) * light[i].lightColor;

	  result = result + ambient + diffuse + specular;
	}
    
	fColour = vec4(result, material.transparency);
}