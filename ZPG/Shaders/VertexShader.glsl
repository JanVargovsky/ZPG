#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

out vec3 ourColor;
out vec4 worldPosition;
out vec4 worldNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = (projection * view * model) * vec4(position, 1.0);
	ourColor = color;
	worldPosition = model * vec4(position, 1.0);
	worldNormal = model * vec4(normal, 1.0);
};