#shader vertex	
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

out vec3 FragPos;
out vec3 Normal;
//layout(location = 1) in vec2 texCoord;

//out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
	FragPos = vec3(u_model * position);
	Normal = normal;
	gl_Position = u_MVP * position;
	//v_TexCoord = texCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
//in vec2 v_TexCoord;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform float ambientStrength;
//uniform sampler2D u_Texture;

void main()
{
	//Toon Shading
	float intensity;
	vec3 color;
	intensity = dot(lightPos, normalize(Normal));

	if (intensity > 0.95)
		color = vec3(1.0, 0.5, 0.5);

	else if (intensity > 0.5)
		color = vec3(0.6, 0.3, 0.3);

	else if (intensity > 0.25)
		color = vec3(0.4, 0.2, 0.2);

	else 
		color = vec3(0.2, 0.1, 0.1);

	//Lighting
	/*vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = ambientStrength + diffuse;*/

	//vec3 result = ambientStrength * lightColor;
	//vec4 texCoord = texture(u_Texture, v_TexCoord);
	//FragColor = vec4(result * objectColor, 1.0);
	FragColor = vec4(color * objectColor, 1.0);

};


