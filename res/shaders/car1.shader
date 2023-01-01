#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 v_Normals;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	v_Normals = normals;
	v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

	sampler2D texture_diffuse0;
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;

	sampler2D texture_specular0;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 fragColor;

in vec2 v_TexCoord;
in vec3 v_Normals;

uniform sampler2D texture_diffuse0;

void main()
{
	vec4 texCoord = texture(texture_diffuse0, v_TexCoord);
	fragColor = vec4(0.2f, 0.8f, 0.5f, 1.0f);
}