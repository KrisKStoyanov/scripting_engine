#version 450 core
precision highp float;

in vec4 VertexColorEx;

out vec4 ColorsOut;

void main(){
	ColorsOut = VertexColorEx;
}