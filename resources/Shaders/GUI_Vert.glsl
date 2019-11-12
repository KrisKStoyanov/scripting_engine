#version 450 core

layout (location = 0) in vec2 Pos;
layout (location = 1) in vec2 UV;
layout (location = 2) in vec4 Color;

out vec4 ExColor;
out vec2 ExUV;

void main(){
	ExColor = Color;
	ExUV = UV;
	gl_Position = vec4(Pos.x, Pos.y, 0.0, 1.0);
}