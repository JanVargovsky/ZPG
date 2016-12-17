#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 worldPosition;
out vec3 worldNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = (projection * view * model) * vec4(position, 1.0f);

	worldPosition = vec3(model * vec4(position, 1.0));
	mat3 m = transpose(inverse(mat3(model)));
	worldNormal = normalize(m * normal);
};