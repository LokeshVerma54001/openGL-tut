#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	//instead of gettins static normals we calculate it 
	//we are multiplying normals by normal matrix
	//normal matrix is transpose of inverse of model matrix
	Normal = mat3(transpose(inverse(model))) * aNormal; 
	//we perform lighting calculations in the world space
	FragPos = vec3(model * vec4(aPos, 1.0));
	//converting the lighting to be in view space
	LightPos = vec3(view * vec4(lightPos, 1.0));
}