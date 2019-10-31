#version 450 core

layout (location = 0) in vec4 VertexPos;
layout (location = 1) in vec4 VertexColor;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 ExFragPos;
out vec4 ExVertexColor;

void main(){
	ExFragPos = vec3(Model * VertexPos);
	ExVertexColor = VertexColor;
	gl_Position = Projection * View * Model * VertexPos;
	//gl_Position = VertexPos;
}