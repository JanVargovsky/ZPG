#version 330 core
in vec3 ourColor;
in vec4 worldPosition;
in vec4 worldNormal;

out vec4 color;

uniform vec3 lightPosition;

void main()
{
	vec3 lightVector= normalize(vec3(0.0f, 5.0f, 0.0f));
	float dotProduct = max(dot(vec4(lightVector, 1.0f), normalize(worldNormal)), 0.0f);
	vec4 diffuse = vec4(dotProduct);
	vec4 ambient = vec4(vec3(0.1f), 1.0f);

	color = (diffuse + ambient) * vec4(0.0f, 0.6f, 1.0f, 1.0f);
};