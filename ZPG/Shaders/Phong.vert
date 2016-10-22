#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 ourColor;
out vec3 worldPosition;
out vec3 worldNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = (projection * view * model) * vec4(position, 1.0);

	ourColor = vec3(0.0f, 0.6f, 1.0f);
	worldPosition = vec3(model * vec4(position, 1.0));
	worldNormal = normalize(transpose(inverse(mat3(model))) * normal);
	ourColor = vec3(1.0f, 0.3f, 0.0f);
};