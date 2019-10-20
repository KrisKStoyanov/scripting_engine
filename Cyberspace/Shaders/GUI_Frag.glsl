#version 450 core
precision highp float;

in vec4 ExColor;
in vec2 ExUV;

uniform sampler2D GUITexture;

void main(){
	FragColor = texture(GUITexture, ExUV) * ExColor;
}