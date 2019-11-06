#version 450 core
precision highp float;
out vec4 FragColor;

in vec2 ExVertexUV;
uniform sampler2D texture1;

void main() {
	FragColor = texture(texture1, ExVertexUV);
}