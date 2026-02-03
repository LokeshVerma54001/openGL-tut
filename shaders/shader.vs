#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float xOffset; 
out vec3 vertexCoords;

void main(){
	vec3 newPos = vec3(aPos.x + xOffset, -aPos.y, aPos.z);
	gl_Position = vec4(newPos, 1.0);
	vertexCoords = aPos;
	ourColor = aColor;
}