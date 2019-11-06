#version 450 core
precision highp float;
out vec4 FragColor;

struct Material {
	sampler2D DiffuseMap;
	sampler2D SpecularMap;
	sampler2D NormalMap;
	sampler2D HeightMap;
	float Shininess;
};

struct Light {
	vec3 Position;
	vec3 AmbientC;
	vec3 DiffuseC;	
	vec3 SpecularC;
};

in vec3 ExFragPos;
in vec3 ExNormal;
in vec2 ExVertexUV;

uniform vec3 ViewPos;
uniform Material g_Material;
uniform Light g_Light;

void main() {
	vec3 AmbientColor = g_Light.AmbientC * texture(g_Material.DiffuseMap, ExVertexUV).rgb;

	vec3 Normal = normalize(ExNormal);
	vec3 LightDir = normalize(g_Light.Position - ExFragPos);

	float DiffuseScalar = max(dot(Normal, LightDir), 0.0f);
	vec3 DiffuseColor = g_Light.DiffuseC * DiffuseScalar * texture(g_Material.DiffuseMap, ExVertexUV).rgb;

	vec3 ViewDir = normalize(ViewPos - ExFragPos);
	vec3 ReflDir = reflect(-LightDir, Normal);

	float SpecularScalar = pow(max(dot(ViewDir, ReflDir), 0.0f), g_Material.Shininess);
	vec3 SpecularColor = g_Light.SpecularC * SpecularScalar * texture(g_Material.SpecularMap, ExVertexUV).rgb;

	vec3 CombinedColor = AmbientColor + DiffuseColor + SpecularColor;
	FragColor = vec4(CombinedColor, 1.0f);
}