#version 450 core

layout (location = 0) in vec3 VertexPos;
layout (location = 1) in vec4 VertexColor;

out vec4 ExVertexColor;

void main(){
	ExVertexColor = VertexColor;
	gl_Position = vec4(VertexPos.x, VertexPos.y, VertexPos.z, 1.0);
}