#version 330 core
in vec3 ourColor;
in vec4 worldPosition;
in vec4 worldNormal;

out vec4 color;

uniform vec3 lightPosition;

void main()
{
	vec3 lightVector= normalize(vec3(0.0, 5.0, 0.0));
	float dotProduct = max(dot(vec4(lightVector, 1.0), normalize(worldNormal)), 0.0);
	vec4 diffuse = vec4(dotProduct);
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

	color = (diffuse + ambient) * vec4(1,0,0,1); // * vec4(ourColor, 1.0);
};