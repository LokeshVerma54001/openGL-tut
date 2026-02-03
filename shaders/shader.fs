#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec3 vertexCoords;

void main(){
    FragColor = vec4(vertexCoords, 1.0);
}