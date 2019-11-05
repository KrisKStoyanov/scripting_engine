#version 450 core
precision highp float;

in vec4 ExVertexColor;

out vec4 FragColor;

void main(){
	FragColor = ExVertexColor;
}