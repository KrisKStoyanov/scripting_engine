#version 450 core

in vec4 VertexPos;
in vec4 VertexColor;

out vec4 VertexColorEx;

void main(){
	VertexColorEx = VertexColor;
	gl_Position = vec4(VertexPos.x, VertexPos.y, VertexPos.z, 1.0);
}